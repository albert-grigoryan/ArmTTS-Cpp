#include "textPreprocessor.hpp"
#include "utilities.hpp"
#include "json.hpp"

#include <curl/curl.h>

#include <algorithm>
#include <iostream>
#include <regex>

namespace VARAGAVAN {
namespace ARMTTS {

std::vector<std::wstring> TextPreprocessor::tokenize(const std::wstring& text)  noexcept {
    std::vector<std::wstring> tokens;
    std::wregex s_full_stops(L"[;։․.]");
    std::wregex s_commas(L"[՝`]");
    std::wstring processedStr = std::regex_replace(text, s_full_stops, L":", std::regex_constants::match_any);
    processedStr = std::regex_replace(processedStr, s_commas, L",", std::regex_constants::match_any);
    std::wistringstream tokenizer(processedStr);
    std::wstring token;
    while (std::getline(tokenizer, token, L':')) {
        if (token.length() <= MAX_LENGTH) {
            tokens.push_back(token + L':');
            continue;
        }
        std::wistringstream word_tokenizer(token);
        std::wstring word;
        std::wstring tmp_string;
        while (word_tokenizer >> word) {
            if (tmp_string.length() + word.length() < MAX_LENGTH) {
                tmp_string += L" " + word;
                if (word.back() == L':') {
                    tokens.push_back(tmp_string);
                    tmp_string.clear();
                } else if (word.length() > MAX_LENGTH / 2 && word.back() == L',') {
                    tokens.push_back(tmp_string);
                    tmp_string.clear();
                }
            } else {
                if (!tmp_string.empty()) {
                    tokens.push_back(tmp_string + L',');
                }
                tmp_string = word;
            }
        }
        if (!tmp_string.empty()) {
            tokens.push_back(tmp_string + L':');
        }
    }

    return tokens;
}


size_t CurlWrite_CallbackFunc_StdString(void *contents, size_t size, size_t nmemb, std::string *s) {
    size_t newLength = size*nmemb;
    s->append((char*)contents, newLength);
    return newLength;
}

std::vector<long> TextPreprocessor::preprocessChunk(const std::string& chunk) noexcept {
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if(curl) {
        std::string response("");  // Response string to store the result
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_URL, API_URL);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        struct curl_slist *headers = NULL;
        const std::string x_RapidAPI_Key_header = "X-RapidAPI-Key: " + X_RapidAPI_Key;
        headers = curl_slist_append(headers, x_RapidAPI_Key_header.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_mime *mime;
        curl_mimepart *part;
        mime = curl_mime_init(curl);
        part = curl_mime_addpart(mime);
        curl_mime_name(part, "text");
        curl_mime_data(part, chunk.c_str(), CURL_ZERO_TERMINATED);
        curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);

        // Perform the request
        res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            nlohmann::json j = nlohmann::json::parse(response);
            if (j.contains("ids")) {
                std::vector<long> ids;
                for (const auto& id : j["ids"]) {
                    ids.push_back(id);
                }
                return ids;
            } else {
                if (j.contains("message")) {
                    std::cerr << "Error: " << j["message"] << std::endl;
                }
            }

        } else {
            std::cerr << "Error: " << curl_easy_strerror(res) << std::endl;
        }
        curl_mime_free(mime);
    }
    curl_easy_cleanup(curl);
    return {};
}

std::vector<std::vector<long>> TextPreprocessor::preprocessText(const std::wstring& text) noexcept {
    std::vector<std::wstring> tokens = tokenize(text);
    std::vector<std::vector<long>> result;
    for (const auto& token : tokens) {
        std::vector<long> ids = preprocessChunk(UTILITIES::convertToBytes(token));
        if (ids.empty()) {
            return {};
        }
        result.push_back(std::move(ids));
    }
    return result;
}

TextPreprocessor::TextPreprocessor(const std::string& x_RapidAPI_Key) noexcept
    : X_RapidAPI_Key(x_RapidAPI_Key)
{
}

}
}
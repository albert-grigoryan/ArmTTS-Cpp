/**
 * @file textPreprocessor.hpp
 *
 * @brief Definition of class @ref VARAGAVAN::ARMTTS::TextPreprocessor
 *
 *  Author: Albert Grigoryan
 *  E-mail: albert_grigoryan@yahoo.com
 *  109/26 Vardanants St.,
 *  Yerevan, 0050, Armenia
 *  Tel:  +374-93-635-380
 *
 *  Copyright © 2022 Albert Grigoryan. All rights reserved.
 */
#pragma once

#include <vector>
#include <string>

namespace VARAGAVAN {
namespace ARMTTS {

class TextPreprocessor {
public:
    TextPreprocessor(const std::string& x_RapidAPI_Key) noexcept;

    std::vector<std::vector<long>> preprocessText(const std::wstring& text) noexcept;

private:
    std::vector<std::wstring> tokenize(const std::wstring& text) noexcept;

    std::vector<long> preprocessChunk(const std::string& chunk) noexcept;

    const std::string X_RapidAPI_Key;
    static constexpr int MAX_LENGTH = 140;
    static constexpr char API_URL[] = "https://armtts1.p.rapidapi.com/v2/preprocess";

};

}}
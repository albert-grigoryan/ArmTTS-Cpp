#include "utilities.hpp"

#include "sndfile.h"

#include <experimental/filesystem>
#include <regex>
#include <string>
#include <vector>

namespace VARAGAVAN {
namespace ARMTTS {
namespace UTILITIES {

void writeWavFile(const std::string& file, std::vector<float>& samples, const int sr) {
    CHECK(! samples.empty(), "Samples array is empty, nothing to write.");
    SF_INFO sfInfo;
    sfInfo.format = SF_FORMAT_WAV | SF_FORMAT_FLOAT;
    sfInfo.channels = 1;
    sfInfo.sections = 1;
    sfInfo.samplerate = sr;
    sfInfo.frames = samples.size();
    SNDFILE* sndFile = sf_open(file.c_str(), SFM_WRITE, &sfInfo);
    sf_write_float(sndFile, samples.data(), samples.size());
    CHECK(! sf_error(sndFile), file + ": Write failure: " + sf_error_number(sf_error(sndFile)));
    sf_write_sync(sndFile);
    sf_close(sndFile);
}

std::wstring convertFromBytes(const std::string s) noexcept {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(s);
}

std::string convertToBytes(const std::wstring s) noexcept {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(s);
}

}}}

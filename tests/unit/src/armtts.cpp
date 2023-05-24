#include "engine.hpp"

#include <gtest/gtest.h>
#include <filesystem>

namespace VARAGAVAN {
namespace ARMTTS {
namespace TESTS {

// Unit Tests

TEST(engineTests, generateAudio) {
    Engine engine("UPDATE X_RapidAPI_Key HERE");
    std::string audio = engine.generateAudio(L"Ողջույն, իմ անունը Գոռ է։");
    std::string expected_audio_file("results/audio_1.wav");
    ASSERT_STREQ(expected_audio_file.c_str(), audio.c_str());
    ASSERT_TRUE(std::filesystem::exists(expected_audio_file));
}

}}}

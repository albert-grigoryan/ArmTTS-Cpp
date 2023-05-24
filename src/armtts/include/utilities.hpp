/**
 * @file utilities.hpp
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

#include "textPreprocessor.hpp"

#include "json.hpp"

#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <complex>

namespace VARAGAVAN {
namespace ARMTTS {
namespace UTILITIES {

#define CHECK(b, e)                           \
if (!(b)) {                                   \
    std::ostringstream o;                     \
    o << "ArmTTS Error: " << e;               \
    throw std::runtime_error(o.str());        \
}

/**
 * @brief Write wav file in Wave&Double format.
 * @param file - file to create/update.
 * @param mels - mel spectogramms.
 * @param sr - sample rate
 */
void writeWavFile(const std::string& file, std::vector<float>& samples, const int sr);

/*
 * @Brief Convert string to Unicode.
 * @param s - string.
 * @return converted Un Unicode string.
 */
std::wstring convertFromBytes(const std::string s) noexcept;

/*
 * @Brief Convert Unicode to string.
 * @param s - string (wide)
 * @return converted string.
 */
std::string convertToBytes(const std::wstring s) noexcept;

}}}

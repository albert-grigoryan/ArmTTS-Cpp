/**
 * @file engine.hpp
 *
 * @brief Definition of class @ref VARAGAVAN::ARMTTS::Engine
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
#include <iostream>
#include <sstream>

namespace Ort {
    class Env;
    class SessionOptions;
    class Session;
};

namespace VARAGAVAN {
namespace ARMTTS {

class TextPreprocessor;

class Engine {
public:
    /**
     * @brief Default constructor.
     **/
    Engine(const std::string& x_RapidAPI_Key) noexcept;

    std::string generateAudio(const std::wstring& sentence, float speed = 1.0f) noexcept;


private:

    std::vector<float> process(std::vector<std::vector<long>>& inputArray, float speed = 1.0f) noexcept;

    std::vector<float> RunONNXModel(std::vector<std::vector<long>>& inputArray,
                                    std::vector<long>& inputLengthsArray, std::vector<float>& scalesArray);


private:
    TextPreprocessor* _textPreprocessor;
    Ort::Env* _ortEnv;
    Ort::SessionOptions* _ortSessionOptions;
    Ort::Session* _ortSession;

    static constexpr int SAMPLE_RATE = 44100;
    static constexpr char RESULTS_DIR[] = "results";
};

}
}
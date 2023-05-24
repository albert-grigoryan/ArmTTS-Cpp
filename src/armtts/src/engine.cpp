#include "engine.hpp"
#include "utilities.hpp"

#include <onnxruntime_cxx_api.h>

#include <cmath>
#include <vector>
#include <filesystem>

namespace VARAGAVAN {
namespace ARMTTS {

std::string Engine::generateAudio(const std::wstring& sentence, float speed) noexcept {
    static int count = 1;
    std::vector<float> result;
    std::vector<std::vector<long>> textIds = _textPreprocessor->preprocessText(sentence);
    if (textIds.empty()) {
        return {};
    }
    for (const auto& inputIds : textIds) {
        std::vector<std::vector<long>> ids{inputIds};
        std::vector<float> chunkResult = process(ids, speed);
        result.insert(result.end(), chunkResult.begin(), chunkResult.end());
    }
    std::ostringstream ss("");
    ss << RESULTS_DIR << '/' << "audio_" << count << ".wav";
    ++count;
    UTILITIES::writeWavFile(ss.str(), result, SAMPLE_RATE);
    return ss.str();
}

std::vector<float> Engine::RunONNXModel(std::vector<std::vector<long>>& inputArray,
                          std::vector<long>& inputLengthsArray, std::vector<float>& scalesArray) {
        Ort::MemoryInfo memoryInfo = Ort::MemoryInfo::CreateCpu(OrtDeviceAllocator, OrtMemTypeCPU);

        // Create input tensors
        std::vector<int64_t> inputTensorDims = { 1, static_cast<int64_t>(inputArray[0].size())};
        Ort::Value inputTensor = Ort::Value::CreateTensor<long>(memoryInfo, inputArray[0].data(), inputArray[0].size(),
                                                            inputTensorDims.data(), inputTensorDims.size());

        std::vector<int64_t> lengthsTensorDims = { static_cast<int64_t>(inputArray.size()) };
        Ort::Value lengthsTensor = Ort::Value::CreateTensor<long>(memoryInfo, inputLengthsArray.data(),
                                                              inputLengthsArray.size(), lengthsTensorDims.data(),
                                                              lengthsTensorDims.size());

        std::vector<int64_t> scalesTensorDims = { 3 };
        Ort::Value scalesTensor = Ort::Value::CreateTensor<float>(memoryInfo, scalesArray.data(), scalesArray.size(),
                                                              scalesTensorDims.data(), scalesTensorDims.size());

        // Prepare inputs
        std::vector<const char*> inputNames = { "input", "input_lengths", "scales" };
        std::vector<Ort::Value> inputTensors;
        inputTensors.reserve(3);
        inputTensors.emplace_back(std::move(inputTensor));
        inputTensors.emplace_back(std::move(lengthsTensor));
        inputTensors.emplace_back(std::move(scalesTensor));

        std::vector<const char*> outputNames = { "output" };
        Ort::Value outputTensor{nullptr};
        std::vector<Ort::Value> outputTensors;
        outputTensors.reserve(1);
        outputTensors.emplace_back(std::move(outputTensor));

        // Run the model
        _ortSession->Run(Ort::RunOptions{nullptr}, inputNames.data(), inputTensors.data(), inputNames.size(),
                    outputNames.data(), outputTensors.data(), outputNames.size());

        // Get the output tensor
        size_t output_tensor_size = outputTensors.front().GetTypeInfo().GetTensorTypeAndShapeInfo().GetElementCount();
        std::vector<float> output_buffer(output_tensor_size);
        float* output_data = outputTensors.front().GetTensorMutableData<float>();
        std::copy(output_data, output_data + output_tensor_size, output_buffer.data());

        return output_buffer;
    }

std::vector<float> Engine::process(std::vector<std::vector<long>>& inputArray, float speed) noexcept {
    std::vector<long> inputLengthsArray(inputArray.size());
    for (size_t i = 0; i < inputArray.size(); ++i) {
        inputLengthsArray[i] = inputArray[i].size();
    }
    std::vector<float> scalesArray{0.333f, speed, 0.0f};

    const std::vector<float> result = RunONNXModel(inputArray, inputLengthsArray, scalesArray);
    return result;
}

Engine::Engine(const std::string& x_RapidAPI_Key) noexcept
    : _textPreprocessor(new TextPreprocessor(x_RapidAPI_Key))
    , _ortEnv(new Ort::Env(ORT_LOGGING_LEVEL_WARNING, "ArmTTS"))
    , _ortSessionOptions(new Ort::SessionOptions())
    , _ortSession(new Ort::Session(*_ortEnv, "models/arm-gor.onnx", *_ortSessionOptions))
{
    assert(nullptr != _textPreprocessor);
    assert(nullptr != _ortEnv);
    assert(nullptr != _ortSessionOptions);
    assert(nullptr != _ortSession);

    assert(3 == _ortSession->GetInputCount());
    assert(1 == _ortSession->GetOutputCount());

    // Check inputs
    assert(2 == _ortSession->GetInputTypeInfo(0).GetTensorTypeAndShapeInfo().GetDimensionsCount());
    assert(ONNX_TENSOR_ELEMENT_DATA_TYPE_INT64 ==
        _ortSession->GetInputTypeInfo(0).GetTensorTypeAndShapeInfo().GetElementType());

    assert(1 == _ortSession->GetInputTypeInfo(1).GetTensorTypeAndShapeInfo().GetDimensionsCount());
    assert(ONNX_TENSOR_ELEMENT_DATA_TYPE_INT64 ==
           _ortSession->GetInputTypeInfo(1).GetTensorTypeAndShapeInfo().GetElementType());

    assert(1 == _ortSession->GetInputTypeInfo(2).GetTensorTypeAndShapeInfo().GetDimensionsCount());
    assert(ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT ==
           _ortSession->GetInputTypeInfo(2).GetTensorTypeAndShapeInfo().GetElementType());
    assert(3 == _ortSession->GetInputTypeInfo(2).GetTensorTypeAndShapeInfo().GetShape().front());

    // Check output
    assert(4 == _ortSession->GetOutputTypeInfo(0).GetTensorTypeAndShapeInfo().GetDimensionsCount());
    assert(ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT ==
        _ortSession->GetOutputTypeInfo(0).GetTensorTypeAndShapeInfo().GetElementType());

    // Create results dir.
    std::filesystem::create_directory(RESULTS_DIR);
}

}}

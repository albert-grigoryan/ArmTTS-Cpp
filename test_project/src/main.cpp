#include <iostream>

#include <armtts/engine.hpp>

int main(int argc, char* argv[]) {
    VARAGAVAN::ARMTTS::Engine engine("UPDATE X_RapidAPI_Key HERE");
    std::string audio = engine.generateAudio(L"Ողջույն, իմ անունը Գոռ է:");
    std::cout << "Result: " << audio << std::endl;
    return 0;
}
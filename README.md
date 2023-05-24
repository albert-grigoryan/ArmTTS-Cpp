# ArmTTS

[![License](https://img.shields.io/cocoapods/l/ArmTTS.svg?style=flat)](https://cocoapods.org/pods/ArmTTS)

## Requirements
Subscribe to one of the available plans in [RapidAPI](https://rapidapi.com/albertgrigoryan/api/armtts1/pricing) and do not forget to update the **'X_RapidAPI_Key'** with the key provided by RapidAPI.

### Installation

```
1. clone the repository
2. mkdir build && cd build && cmake .. && make -j
3. sudo make install
```

### Usage

After the library is built and installed, follow the steps below:

1. Subscribe to one of the available plans in [RapidAPI](https://rapidapi.com/albertgrigoryan/api/armtts1/pricing)

2. Update the **'X_RapidAPI_Key'**  with the key provided by RapidAPI in **test_project/src/main.cpp**
 
3. Build and run
 
```
1. cd test_project
2. mkdir build && cd build && cmake .. && make -j && cd ..
3. export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib/
4. ./build/test_project
```

## Author

Albert Grigoryan, albert_grigoryan@yahoo.com

## License

ArmTTS is available under the MIT license. See the LICENSE file for more info.
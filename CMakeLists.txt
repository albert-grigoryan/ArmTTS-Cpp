cmake_minimum_required(VERSION 2.8.12...3.13)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-Werror")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set(CMAKE_INCLUDES_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/includes )
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

# Install Dirs
set(INSTALL_LIB_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(INSTALL_INCLUDE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/include/armtts)
set(INSTALL_PKGCONFIG_DIRECTORY ${INSTALL_LIB_DIRECTORY}/pkgconfig)

#set(CMAKE_VERBOSE_MAKEFILE ON)
set(EP_DEPENDENCIES_PATH "${CMAKE_BINARY_DIR}/Dependencies")

# Project Properties
set(PROJECT_NAME         "ArmTTS")
set(PROJECT_VERSION      "2.0.0")
set(PROJECT_DESCRIPTION  "ML based Text-to-Speech(TTS) engine for the Armenian language.")
set(PROJECT_AUTHOR_NAME  "Albert Grigoryan")
set(PROJECT_AUTHOR_EMAIL "albert_grigoryan@yahoo.com")
project(${PROJECT_NAME})

# Add general dependencies
add_subdirectory(third_party/curl)
add_subdirectory(third_party/nlohmannjson)
add_subdirectory(third_party/sndfile)
add_subdirectory(third_party/onnxruntime)

# Add projects
add_subdirectory(src/armtts)

# Add the tests and the documentation.
add_subdirectory(third_party/gtest)
add_subdirectory(tests/unit)
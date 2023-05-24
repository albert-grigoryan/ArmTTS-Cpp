cmake_minimum_required(VERSION 2.8.12...3.13)
project(test_project)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-Werror")

# Find the ArmTTS library package using pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(ARMTTS REQUIRED armtts)

file(GLOB SOURCES "src/*.c" "src/*.cpp")
add_executable(test_project ${SOURCES})

# Link the executable with the armtts library
target_link_libraries(test_project ${ARMTTS_LIBRARIES})
target_include_directories(test_project PRIVATE ${ARMTTS_INCLUDE_DIRS})
target_compile_options(test_project PRIVATE ${ARMTTS_CFLAGS_OTHER})
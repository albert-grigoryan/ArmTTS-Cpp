include(ExternalProject)

set(NAME gtest)
set(VERSION 1.13.0)
set(PREFIX ${EP_DEPENDENCIES_PATH}/${NAME})

message (STATUS "Adding ${NAME}:${VERSION} as an external project.")

ExternalProject_Add(${NAME}
  URL https://github.com/google/googletest/archive/refs/tags/v${VERSION}.tar.gz
  UPDATE_DISCONNECTED ON
  CMAKE_ARGS
    "-DCMAKE_INSTALL_PREFIX=${PREFIX}"
    "-DCMAKE_BUILD_TYPE:STRING=Release"
)

set(GTEST_INCLUDE_DIR ${PREFIX}/include PARENT_SCOPE)
set(GTEST_LIB_DIR ${PREFIX}/lib PARENT_SCOPE)
set(GTEST_LIBRARIES
    -lgtest
    -lgtest_main
PARENT_SCOPE)

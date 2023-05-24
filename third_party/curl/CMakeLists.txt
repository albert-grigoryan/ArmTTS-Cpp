include(ExternalProject)

set(NAME curl)
set(VERSION 8.0.0)
set(PREFIX ${EP_DEPENDENCIES_PATH}/${NAME})

message (STATUS "Adding ${NAME}:${VERSION} as an external project.")

ExternalProject_Add(${NAME}
  URL https://github.com/curl/curl/releases/download/curl-8_0_0/curl-${VERSION}.tar.gz
  UPDATE_DISCONNECTED ON
  CMAKE_ARGS
    "-DCMAKE_INSTALL_PREFIX=${PREFIX}"
    "-DCMAKE_BUILD_TYPE:STRING=Release"
)

set(CURL_INCLUDE_DIR ${PREFIX}/include PARENT_SCOPE)
set(CURL_LIB_DIR ${PREFIX}/lib PARENT_SCOPE)
set(CURL_LIBRARIES
    -lcurl
PARENT_SCOPE)

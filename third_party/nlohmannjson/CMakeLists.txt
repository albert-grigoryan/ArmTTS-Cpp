include(ExternalProject)

set(NAME nlohmannjson)
set(VERSION 3.9.1)
set(PREFIX ${EP_DEPENDENCIES_PATH}/${NAME})

message (STATUS "Adding ${NAME}:${VERSION} as an external project.")

ExternalProject_Add(${NAME}
  DOWNLOAD_NO_EXTRACT ON
  UPDATE_DISCONNECTED ON
  URL https://github.com/nlohmann/json/releases/download/v${VERSION}/json.hpp
  PATCH_COMMAND ""
  CONFIGURE_COMMAND ""
  CMAKE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND mkdir -p ${PREFIX}/include && cp ../json.hpp ${PREFIX}/include
)

set(NLOHMANNJSON_INCLUDE_DIR ${PREFIX}/include PARENT_SCOPE)

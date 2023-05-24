include(ExternalProject)

set(NAME onnxruntime)
set(VERSION 1.13.1)
set(PREFIX ${EP_DEPENDENCIES_PATH}/${NAME})

message (STATUS "Adding ${NAME}:${VERSION} as an external project.")

ExternalProject_Add(${NAME}
  GIT_REPOSITORY  https://github.com/Microsoft/onnxruntime.git
  GIT_TAG v${VERSION}
  GIT_SUBMODULES_RECURSE ON
  UPDATE_DISCONNECTED ON
  CONFIGURE_COMMAND ""
  CMAKE_COMMAND ""
  BUILD_COMMAND cd ../onnxruntime && ./build.sh --config MinSizeRel --build_shared_lib --parallel
  INSTALL_COMMAND
      mkdir -p ${PREFIX}/include &&
        cp ../onnxruntime/include/onnxruntime/core/session/environment.h
           ../onnxruntime/include/onnxruntime/core/session/experimental_onnxruntime_cxx_api.h
           ../onnxruntime/include/onnxruntime/core/session/experimental_onnxruntime_cxx_inline.h
           ../onnxruntime/include/onnxruntime/core/session/onnxruntime_c_api.h
           ../onnxruntime/include/onnxruntime/core/session/onnxruntime_cxx_api.h
           ../onnxruntime/include/onnxruntime/core/session/onnxruntime_cxx_inline.h
           ../onnxruntime/include/onnxruntime/core/session/onnxruntime_run_options_config_keys.h
           ../onnxruntime/include/onnxruntime/core/session/onnxruntime_session_options_config_keys.h
        ${PREFIX}/include &&
      mkdir -p ${PREFIX}/lib &&
        cp  ../onnxruntime/build/Linux/MinSizeRel/libcustom_op_library.so
            ../onnxruntime/build/Linux/MinSizeRel/libonnxruntime.so
            ../onnxruntime/build/Linux/MinSizeRel/libonnxruntime.so.${VERSION}
            ../onnxruntime/build/Linux/MinSizeRel/libonnxruntime_providers_shared.so
            ../onnxruntime/build/Linux/MinSizeRel/libtest_execution_provider.so
        ${PREFIX}/lib;
)

set(ONNXRUNTIME_INCLUDE_DIR ${PREFIX}/include PARENT_SCOPE)
set(ONNXRUNTIME_LIB_DIR ${PREFIX}/lib PARENT_SCOPE)
set(ONNXRUNTIME_LIBRARIES -lonnxruntime PARENT_SCOPE)

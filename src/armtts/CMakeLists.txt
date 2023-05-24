get_filename_component(SUB_PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

file(GLOB SOURCES "src/*.c" "src/*.cpp")
add_library(${SUB_PROJECT_NAME} SHARED ${SOURCES})
add_dependencies(${SUB_PROJECT_NAME}
        curl
        nlohmannjson
        sndfile
        onnxruntime
)

target_link_directories(${SUB_PROJECT_NAME} PUBLIC
        ${CURL_LIB_DIR}
        ${SNDFILE_LIB_DIR}
        ${ONNXRUNTIME_LIB_DIR}
)
target_link_libraries(${SUB_PROJECT_NAME} LINK_PUBLIC
        ${CURL_LIBRARIES}
        ${SNDFILE_LIBRARIES}
        ${ONNXRUNTIME_LIBRARIES}
)
target_include_directories(${SUB_PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
        ${CURL_INCLUDE_DIR}
        ${NLOHMANNJSON_INCLUDE_DIR}
        ${SNDFILE_INCLUDE_DIR}
        ${ONNXRUNTIME_INCLUDE_DIR}
)
# Install
install(TARGETS ${SUB_PROJECT_NAME} DESTINATION ${INSTALL_LIB_DIRECTORY})
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
        DESTINATION ${INSTALL_INCLUDE_DIRECTORY}
        FILES_MATCHING PATTERN "engine.hpp"
)
install(FILES armtts.pc
        DESTINATION ${INSTALL_PKGCONFIG_DIRECTORY}
)
install(FILES
        ${EP_DEPENDENCIES_PATH}/curl/lib/libcurl.so
        ${EP_DEPENDENCIES_PATH}/curl/lib/libcurl.so.4
        ${EP_DEPENDENCIES_PATH}/curl/lib/libcurl.so.4.8.0
        ${EP_DEPENDENCIES_PATH}/onnxruntime/lib/libcustom_op_library.so
        ${EP_DEPENDENCIES_PATH}/onnxruntime/lib/libonnxruntime.so
        ${EP_DEPENDENCIES_PATH}/onnxruntime/lib/libonnxruntime.so.1.13.1
        ${EP_DEPENDENCIES_PATH}/onnxruntime/lib/libonnxruntime_providers_shared.so
        ${EP_DEPENDENCIES_PATH}/sndfile/lib/libsndfile.so
        ${EP_DEPENDENCIES_PATH}/sndfile/lib/libsndfile.so.1
        ${EP_DEPENDENCIES_PATH}/sndfile/lib/libsndfile.so.1.0.28
        DESTINATION ${INSTALL_LIB_DIRECTORY}
)

set(SUB_PROJECT_NAME unit_tests)

file(GLOB SOURCES "src/*.c" "src/*.cpp")
add_executable(${SUB_PROJECT_NAME} ${SOURCES})
add_dependencies(${SUB_PROJECT_NAME}
        gtest
        armtts
)

target_link_directories(${SUB_PROJECT_NAME} PUBLIC
        ${GTEST_LIB_DIR}
)
target_link_libraries(${SUB_PROJECT_NAME} LINK_PUBLIC
        armtts
        ${GTEST_LIBRARIES}
)
target_include_directories(${SUB_PROJECT_NAME} PUBLIC
        ${GTEST_INCLUDE_DIR}
)
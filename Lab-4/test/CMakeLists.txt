cmake_minimum_required(VERSION 3.21.0)

file(GLOB TEST_SOURCES
    *.cpp
)

set(TEST_EXECUTABLE "${PROJECT_NAME}-test")

add_executable(${TEST_EXECUTABLE} ${TEST_SOURCES})

target_include_directories(${TEST_EXECUTABLE} PRIVATE "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(${TEST_EXECUTABLE} gtest ${LIB_NAME})

include(GoogleTest)
gtest_discover_tests(${TEST_EXECUTABLE})

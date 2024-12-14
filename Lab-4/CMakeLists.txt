cmake_minimum_required(VERSION 3.21.0)

project(Lab-4 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

file(GLOB SOURCES
    src/*.cpp
    src/*.h
)

file(GLOB HEADERS
    include/*.cpp
    include/*.h
)
set(LIB_NAME "${PROJECT_NAME}-lib")
message(STATUS "Sources: ${SOURCES},
                Headers: ${HEADERS}")

enable_testing()
add_library(${LIB_NAME} ${SOURCES})
add_subdirectory(test)


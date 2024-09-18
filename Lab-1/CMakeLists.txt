cmake_minimum_required(VERSION 3.15.0)

project(Lab-1 LANGUAGES CXX)

set(PROJECT_SOURCES
    "src/main.cpp"
    "src/generator.cpp"
    "src/generator.h"
    "src/variable-types.h"
    "src/parser.h"
    "src/parser.cpp"
)

add_executable(lab-1 ${PROJECT_SOURCES})

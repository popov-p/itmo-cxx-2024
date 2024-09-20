cmake_minimum_required(VERSION 3.15.0)

project(Lab-1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
  "src/main.cpp"
  "src/generator.cpp"
  "src/generator.h"
  "src/parser.h"
)

add_executable(lab-1 ${PROJECT_SOURCES})

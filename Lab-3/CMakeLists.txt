cmake_minimum_required(VERSION 3.10)

project(Lab-3 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

file(GLOB SOURCES
    src/*.cpp
    src/*.h
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_options(${PROJECT_NAME} PRIVATE
    -DNDEBUG
    -Wall -Wextra -Wpedantic -Werror
    -g
    -fsanitize=address,undefined,leak
)

target_link_options(${PROJECT_NAME} PRIVATE
    -fsanitize=address,undefined,leak
)

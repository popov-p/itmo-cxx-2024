cmake_minimum_required(VERSION 3.21.0)

project(Lab-2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER clang++)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
endif()

FILE(GLOB_RECURSE SOURCES
    src/*.h
    src/*.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

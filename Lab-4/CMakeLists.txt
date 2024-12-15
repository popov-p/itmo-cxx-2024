cmake_minimum_required(VERSION 3.21.0)

project(Lab-4 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

file(GLOB SOURCES
    src/*.cpp
    src/*.h
)

file(GLOB_RECURSE HEADERS
    include/*.cpp
    include/*.h
)

source_group("Headers" FILES ${HEADERS})
source_group("Sources" FILES ${SOURCES})

set(TIME_PLOT_BUILDER "${PROJECT_NAME}-time")
add_executable(${TIME_PLOT_BUILDER} ${SOURCES} ${HEADERS})
target_include_directories(${TIME_PLOT_BUILDER} PRIVATE "${PROJECT_SOURCE_DIR}/include")

enable_testing()
add_subdirectory(test)


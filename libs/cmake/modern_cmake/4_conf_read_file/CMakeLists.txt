cmake_minimum_required(VERSION 3.12...3.18)

project(1_add_executable VERSION 2.3.4
                         DESCRIPTION "1st example: add_executable"
                         LANGUAGES CXX)

file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "you cannot build in a source directory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

string(TIMESTAMP BUILD_TIME [%Y-%m-%d_%H:%M:%S])
message(STATUS "BUILD_TIME: " ${BUILD_TIME})

configure_file(
    "${PROJECT_SOURCE_DIR}/version.h.in"
    "${PROJECT_BINARY_DIR}/version.h"
)

include_directories(${PROJECT_BINARY_DIR})
add_executable(a.out helloworld.cpp)

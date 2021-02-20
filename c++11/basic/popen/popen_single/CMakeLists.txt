cmake_minimum_required(VERSION 3.18)

project(popen_test
    VERSION 1.0.0
    LANGUAGES C CXX)

add_library(popen_single popen_single.cpp)

add_executable(main main.cpp)
target_link_libraries(main PUBLIC popen_single)


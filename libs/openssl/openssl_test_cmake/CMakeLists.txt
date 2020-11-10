cmake_minimum_required(VERSION 3.8...3.18)

project(main 
    VERSION 0.0.1
    LANGUAGES CXX)

add_library(base64 base64.cpp)
add_library(tohex tohex.cpp)

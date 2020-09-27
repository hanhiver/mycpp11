cmake_minimum_required(VERSION 3.12...3.18)

project(1_add_executable VERSION 1.0
                         DESCRIPTION "1st example: add_executable"
                         LANGUAGES CXX)

add_subdirectory(hello)

add_executable(a.out main.cpp)

target_include_directories(hello PUBLIC hello)
target_link_libraries(a.out hello)
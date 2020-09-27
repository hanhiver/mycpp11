cmake_minimum_required(VERSION 3.12...3.18)

project(1_add_executable VERSION 1.0
                         DESCRIPTION "1st example: add_executable"
                         LANGUAGES CXX)

add_executable(a.out helloworld.cpp)
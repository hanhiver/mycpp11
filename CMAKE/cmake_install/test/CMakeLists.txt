cmake_minimum_required(VERSION 3.18)
project(test 
    VERSION 1.0.1 
    LANGUAGES CXX)

find_package(MyMath 1.0)

add_executable(test main.cpp)
target_link_libraries(test MyMath::mymath)

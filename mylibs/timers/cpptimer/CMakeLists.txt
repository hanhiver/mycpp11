cmake_minimum_required(VERSION 3.8...3.18)

project(cpptimer
    VERSION 1.0.0
    LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++11")

find_package(Threads REQUIRED)
add_executable(timer_test timer_test.cpp)
target_link_libraries(timer_test PUBLIC Threads::Threads)

add_executable(main main.cpp)
target_link_libraries(main PUBLIC Threads::Threads)

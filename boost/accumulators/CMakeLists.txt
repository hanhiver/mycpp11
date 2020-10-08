cmake_minimum_required(VERSION 3.18)

project(accumulators
        VERSION 1.0.0
        LANGUAGES CXX)

#find_package(Boost REQUIRED COMPONENTS accumulators)
find_package(Boost REQUIRED)
#include_directories(${Boost_INCLUDE_DIRS})

add_executable(a.out simple_example.cpp)
#target_link_libraries(a.out PRIVATE Boost::accumulators)
cmake_minimum_required(VERSION 3.18)

project(main
    VERSION 1.0.0
    LANGUAGES C CXX)

#SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall -fPIC -std=c++11")

add_library(hello STATIC hello.cpp)
target_link_libraries(hello 
    PRIVATE world)
set_property(TARGET hello PROPERTY POSITION_INDEPENDENT_CODE ON)
set_property(TARGET hello PROPERTY LINK_SEARCH_START_STATIC ON)

add_library(world STATIC world.cpp)
set_property(TARGET world PROPERTY POSITION_INDEPENDENT_CODE ON)

add_executable(main main.cpp)
target_link_libraries(main
    PRIVATE hello)
#    PRIVATE world)
set_property(TARGET main PROPERTY POSITION_INDEPENDENT_CODE ON)
set_property(TARGET main PROPERTY LINK_SEARCH_START_STATIC ON)

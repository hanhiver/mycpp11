cmake_minimum_required(VERSION 3.12...3.18)

project(nlohmann_json_test
    VERSION 1.0.0
    LANGUAGES CXX)
include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(simple_test simple_test.cpp)
#target_include_directories(simple_test PUBLIC ${PROJECT_SOURCE_DIR})
cmake_minimum_required(VERSION 3.8...3.18)
project(glogtest
    VERSION 1.0.0
    LANGUAGES CXX)

find_package(glog REQUIRED)

include_directories(${GLOG_INCLUDE_DIRS}})
link_libraries(glog::glog)

add_executable(first_test first_test.cpp)
add_executable(vlog_test vlog_test.cpp)
add_executable(init_test init_test.cpp)

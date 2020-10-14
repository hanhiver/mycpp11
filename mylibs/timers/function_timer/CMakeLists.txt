cmake_minimum_required(VERSION 3.8...3.18)

project(timer
    VERSION 1.0.0.1
    LANGUAGES CXX)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(timer_test timer_test.cpp)
#target_include_directories(timer_test 
#    PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(timer_test
    PRIVATE timer
    PUBLIC Threads::Threads)

add_executable(timer_shutdown timer_shutdown.cpp)
target_link_libraries(timer_shutdown
    PRIVATE timer
    PUBLIC Threads::Threads)

add_subdirectory(src)

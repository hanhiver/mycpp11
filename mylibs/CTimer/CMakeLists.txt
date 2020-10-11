cmake_minimum_required(VERSION 3.8...3.18)

project(CTimer
    VERSION 1.0.0.0
    LANGUAGES CXX)

find_package(Threads REQUIRED)

add_executable(event_test event_test.cpp)
add_executable(thread_pool_test thread_pool_test.cpp)
add_executable(mutex_obj_test mutex_obj_test.cpp)

target_link_libraries(event_test PUBLIC Threads::Threads)
target_link_libraries(thread_pool_test PUBLIC Threads::Threads)
target_link_libraries(mutex_obj_test PUBLIC Threads::Threads)
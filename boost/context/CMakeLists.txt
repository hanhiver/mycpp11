cmake_minimum_required(VERSION 3.4.0)
project(context)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-g -std=c++11")
find_package(Boost REQUIRED COMPONENTS
context 
)

if(NOT Boost_FOUND)
    message(FATAL "Boost not found. ")
endif()

include_directories(${Boost_INCLUDE_DIRS})
message("${Boost_INCLUDE_DIRS}")
message("${Boost_LIBRARIES}")

add_executable(context.out context.cpp)
target_link_libraries(context.out ${Boost_LIBRARIES})

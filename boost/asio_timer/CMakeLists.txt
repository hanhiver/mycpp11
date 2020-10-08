cmake_minimum_required(VERSION 3.8...3.18)

project(asio_timer
        VERSION 1.0.0
        LANGUAGES CXX)

find_package(Boost REQUIRED COMPONENTS 
asio
)

if(NOT Boost_FOUND)
    message(FATAL "Boost not found. ")
endif()

include_directories(${Boost_INCLUDE_DIRS})
message("${Boost_INCLUDE_DIRS}")
message("${Boost_LIBRARIES}")

#find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(asio_timer asio_timer.cpp)
target_link_libraries(asio_timer ${Boost_LIBRARIES})
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

file(GLOB source_files *.cpp)
foreach(file ${source_files})
    get_filename_component(source_we ${source_files} NAME_WE)
    message("source_we: " ${source_we})
    list(APPEND executable ${source_we}.out)
endforeach()

#set(executables ${source_we}.out)
message("executables: " ${executables})

add_executable(circular_buffer.out circular_buffer.cpp)
target_link_libraries(circular_buffer.out ${Boost_LIBRARIES})

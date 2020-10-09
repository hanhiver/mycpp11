cmake_minimum_required(VERSION 3.8...3.18)
set(CMAKE_VERBOSE_MAKEFILE ON)

project(sdk_online_manager
    VERSION 0.1.1
    LANGUAGES CXX)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")

find_package(Threads REQUIRED)
find_package(Gflags REQUIRED)

File(GLOB PROTO_FILES proto/*.proto)

find_package(Protobuf REQUIRED)
if (PROTOBUF_FOUND)
    message(STATUS "protobuf library found.")
    message(STATUS "Protobuf_INCLUDE_DIRS: " ${Protobuf_INCLUDE_DIRS})
    message(STATUS "CMAKE_CURRENT_BINARY_DIR: " ${CMAKE_CURRENT_BINARY_DIR})
    message(STATUS "Protobuf_LIBRARIES: " ${Protobuf_LIBRARIES})
    include_directories(${Protobuf_INCLUDE_DIRS})
    include_directories(${CMAKE_CURRENT_BINARY_DIR})
else()
    message(FATAL_ERROR "protobuf library not found.")
endif()

message(STATUS "PROTO_FILES" ${PROTO_FILES})
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})
add_library(proto_config SHARED ${PROTO_SRCS} ${PROTO_HDRS})

SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

add_executable(sdk_test sdk_test.cpp)
target_include_directories(sdk_test 
    PUBLIC ${CMAKE_SOURCE_DIR}/src/cores
    PUBLIC ${CMAKE_SOURCE_DIR}/src/copenssl
    PUBLIC ${CMAKE_SOURCE_DIR}/src/nlohmann)

target_link_libraries(sdk_test 
    PUBLIC cores
    PUBLIC copenssl
    PUBLIC proto_config
    PUBLIC ${Protobuf_LIBRARIES})

add_subdirectory(src)

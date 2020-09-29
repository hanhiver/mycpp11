# 设定cmake的版本需求
cmake_minimum_required(VERSION 3.12...3.18)

# 设定项目名称，相关的说明和语言
project(1_add_executable VERSION 1.0
                         DESCRIPTION "1st example: add_executable"
                         LANGUAGES CXX)

# 设置本项目使用的c++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Threads REQUIRED)
find_package(Gflags REQUIRED)

File(GLOB PROTO_FILES proto/*.proto)

find_package(Protobuf REQUIRED)
if (PROTOBUF_FOUND)
    message(STATUS "protobuf library found.")
else()
    message(FATAL_ERROR "protobuf library not found.")
endif()

message(STATUS "PROTO_FILES" ${PROTO_FILES})
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})
add_library(proto_config ${PROTO_SRCS} ${PROTO_HDRS})
#target_include_directories(proto PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

# 添加hello子文件夹
add_subdirectory(src)
add_subdirectory(apps)

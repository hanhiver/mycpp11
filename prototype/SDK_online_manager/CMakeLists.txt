cmake_minimum_required(VERSION 3.4.0)
set(CMAKE_VERBOSE_MAKEFILE ON)

project(sdk_online_manager)

set(TARGET_VERSION "0.1.1")
set(TARGET_SOVERSION "0.1")

# --- [ Includes
#set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src
#                        ${PROJECT_SOURCE_DIR}/proto)
#include_directories(${PROJECT_INCLUDE_DIR}
#                    ${PROJECT_BINARY_DIR})

# --- [ Dependency
#include (cmake/Dependency.cmake)

if (UNIX OR APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
endif()

find_package(Threads REQUIRED)
find_package(Gflags REQUIRED)

set(SRC_DIR "./src")
set(CMAKE_INSTALL_PREFIX /usr/local)

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

include_directories(${PROTOBUF_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

# 自动添加.目录下所有的Source文件到变量DIR_LIB_SRCS中。
#aux_source_directory(. DIR_LIB_SRCS)
# 生成链接库
#add_library(core ${DIR_LIB_SRCS})

#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
#INCLUDE_DIRECTORIES(${PROTO_HDRS})
#add_executable(s_test main.cpp ${PROTO_SRCS} ${PROTO_HDRS})

#target_link_libraries(s_test ${PROTOBUF_LIBRARIES})
add_subdirectory(${SRC_DIR})
add_executable(sdk_test src/sdk_test.cpp ${PROTO_SRCS} ${PROTO_HDRS})

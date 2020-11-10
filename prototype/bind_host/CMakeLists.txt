cmake_minimum_required(VERSION 3.8...3.18)
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

project(bind_host_test
    VERSION 0.1.1
    LANGUAGES CXX)

string(TIMESTAMP BUILD_TIME [%Y-%m-%d_%H:%M:%S])
message(STATUS "BUILD_TIME: " ${BUILD_TIME})

configure_file(
    "${PROJECT_SOURCE_DIR}/version.h.in"
    "${PROJECT_BINARY_DIR}/version.h"
)

message(STATUS "CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE})

if(${CMAKE_BUILD_TYPE} MATCHES "Release")
    message(STATUS "Release MODE.")
    SET(CMAKE_BUILD_TYPE "Release")
elseif(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    message(STATUS "Debug MODE.")
    SET(CMAKE_BUILD_TYPE "Debug")
else()
    message(STATUS "Invalide CMAKE_BUILD_TYPE setting, Release Mode.")
    SET(CMAKE_BUILD_TYPE "Release")
endif()

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -fPIC -ggdb -std=c++11")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall -fPIC -std=c++11")

set(CMAKE_CXX_FLAGS "-static ${CMAKE_CXX_FLAGS}")

#if (USE_TCMALLOC)
    #link_libraries(/usr/local/lib/libtcmalloc.a unwind)
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free")
#    link_libraries(tcmalloc)
#endif(USE_TCMALLOC)

find_package(Threads REQUIRED)
#find_package(Gflags REQUIRED)
#find_package(glog REQUIRED)
find_package(OpenSSL REQUIRED)

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
add_library(proto_config STATIC ${PROTO_SRCS} ${PROTO_HDRS})

SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

add_executable(bind_test bind_test.cpp)
target_include_directories(bind_test
    PUBLIC ${CMAKE_SOURCE_DIR}/include
    PUBLIC ${GLOG_INCLUDE_DIRS})
target_link_libraries(bind_test 
    PUBLIC bind_host)

add_subdirectory(src)

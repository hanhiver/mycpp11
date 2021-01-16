cmake_minimum_required(VERSION 3.2...3.18)

if(CMAKE_HOST_WIN32)
    message(STATUS "Build in Windows platform. ")
    set(WINDOWS 1)
elseif (CMAKE_HOST_UNIX)
    message(STATUS "Build in Linux platform. ")
    set(LINUX 1)
elseif (CMAKE_HOST_APPLE)
    message(STATUS "Build in MacOS platform. ")
    set(MACOS 1)
endif()

project(bind_host_test
    VERSION 0.1.1
    LANGUAGES CXX C)

#add_custom_command(TARGET build_estring_head_file PRE_BUILD
file(COPY 
    ${CMAKE_SOURCE_DIR}/gen_code.py 
    ${CMAKE_SOURCE_DIR}/pri.pem 
    ${CMAKE_SOURCE_DIR}/pub.pem 
    ${CMAKE_SOURCE_DIR}/estring.h
    DESTINATION ${CMAKE_BINARY_DIR}/seckeys)
#add_custom_command(OUTPUT pri.h pub.h
add_custom_target(cstring_head ALL
    DEPENDS pri.pem pub.pem
    COMMAND python gen_code.py pri.pem pub.pem 
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/seckeys
    COMMENT "Build the .h file from .pem keys...")

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

if(LINUX)
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -fPIC -ggdb -std=c++11")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall -fPIC -std=c++11")
endif()

find_package(Boost REQUIRED)

#add_executable(build_estring_head_file pub.pem pri.pem)
add_executable(slash test.cpp)
target_include_directories(slash PRIVATE ${CMAKE_BINARY_DIR}/seckeys)
target_link_libraries(slash Boost::boost)

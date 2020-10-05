cmake_minimum_required(VERSION 3.12...3.18)

project(
    chttpclient 
    VERSION 1.0
    DESCRIPTION "test program of libcurl."
    LANGUAGES CXX)

find_package(CURL REQUIRED)

add_library(chttpclient chttpclient.cpp)
add_executable(chttpclient_test chttpclient_test.cpp)

target_include_directories(chttpclient PUBLIC ${CURL_INCLUDE_DIR})
target_link_libraries(chttpclient PUBLIC curl)
target_include_directories(chttpclient_test PUBLIC ${CURL_INCLUDE_DIR})
target_link_libraries(chttpclient_test 
    PUBLIC chttpclient
    PUBLIC curl)


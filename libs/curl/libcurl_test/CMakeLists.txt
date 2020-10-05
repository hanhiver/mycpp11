cmake_minimum_required(VERSION 3.12...3.18)

project(
    curl_test 
    VERSION 1.0
    DESCRIPTION "test program of libcurl.")

find_package(CURL REQUIRED)

include_directories(${CURL_INCLUDE_DIR})
link_libraries(curl)

add_executable(curl_easy_init curl_easy_init.c)
add_executable(curl_version curl_version.cpp)
add_executable(http_post_c http_post.c)
add_executable(post_callback_c post_callback_c.c)
add_executable(save_page save_page.cpp)

#include_directories(${CURL_INCLUDE_DIR})
#link_libraries(curl)
#target_include_directories(curl_easy_init PUBLIC ${CURL_INCLUDE_DIR})
#target_link_libraries(curl_easy_init PUBLIC curl)
#target_link_libraries(curl_version PUBLIC curl)

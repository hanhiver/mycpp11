cmake_minimum_required(VERSION 3.8)
set(CMAKE_VERBOSE_MAKEFILE ON)

project(copenssl)

set(TARGET_VERSION "0.1.1")

find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)

#aux_source_directory(. DIR_SRCS)

add_library(copenssl SHARED COpenSSL.cpp)
add_library(base64 SHARED base64.cpp)
add_executable(COpenSSL_test COpenSSL_test.cpp)

target_link_libraries(copenssl 
                      ${THREADS_PREFER_PTHREAD_FLAG} 
                      ${OPENSSL_CRYPTO_LIBRARIES}
                     )

target_link_libraries(COpenSSL_test 
                      copenssl 
                      base64 
                      ${THREADS_PREFER_PTHREAD_FLAG} 
                      ${OPENSSL_CRYPTO_LIBRARIES}
                     )

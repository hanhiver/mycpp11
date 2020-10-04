cmake_minimum_required(VERSION 3.8)
set(CMAKE_VERBOSE_MAKEFILE ON)

project(copenssl
        VERSION 0.1.2
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)
find_library(MATH_LIBRARY m REQUIRED)

#aux_source_directory(. DIR_SRCS)

add_library(copenssl SHARED COpenSSL.cpp)
add_library(base64 SHARED base64.cpp)
add_executable(COpenSSL_test COpenSSL_test.cpp)

target_link_libraries(copenssl PRIVATE
                      base64
                      ${THREADS_PREFER_PTHREAD_FLAG} 
                      ${OPENSSL_CRYPTO_LIBRARIES}
                      ${MATH_LIBRARY}
                     )

target_link_libraries(COpenSSL_test PRIVATE
                      copenssl 
                      base64 
                      ${THREADS_PREFER_PTHREAD_FLAG} 
                      ${OPENSSL_CRYPTO_LIBRARIES}
                     )

set_target_properties(copenssl PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_compile_features(copenssl PUBLIC cxx_std_11)
set_target_properties(copenssl PROPERTIES CXX_EXTENSIONS OFF)

cmake_minimum_required(VERSION 3.8)
set(CMAKE_VERBOSE_MAKEFILE OFF)

project(
    copenssl
    VERSION 0.1.2
    LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)
find_library(MATH_LIBRARY m REQUIRED)

SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
add_executable(COpenSSL_test COpenSSL_test.cpp)

target_link_libraries(
    COpenSSL_test
    PRIVATE copenssl 
    PRIVATE ${THREADS_PREFER_PTHREAD_FLAG} 
    PRIVATE ${OPENSSL_CRYPTO_LIBRARIES})

target_compile_features(COpenSSL_test PUBLIC cxx_std_11)
set_target_properties(COpenSSL_test PROPERTIES CXX_EXTENSIONS OFF)

#add_executable(commmunicate_java_test commmunicate_java_test.cpp)
#target_link_libraries(
#    commmunicate_java_test
#    PRIVATE copenssl 
#    PRIVATE ${THREADS_PREFER_PTHREAD_FLAG} 
#    PRIVATE ${OPENSSL_CRYPTO_LIBRARIES})

#target_compile_features(commmunicate_java_test PUBLIC cxx_std_11)
#set_target_properties(commmunicate_java_test PROPERTIES CXX_EXTENSIONS OFF)

add_executable(3des_test 3des_test.c)
target_link_libraries(3des_test
    #PRIVATE copenssl 
    #PRIVATE ${THREADS_PREFER_PTHREAD_FLAG} 
    PRIVATE ${OPENSSL_CRYPTO_LIBRARIES})

add_subdirectory(src)
cmake_minimum_required(VERSION 3.2...3.18)
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

project(bind_host_test
    VERSION 0.1.1
    LANGUAGES CXX)

string(TIMESTAMP BUILD_TIME [%Y-%m-%d_%H:%M:%S])
message(STATUS "BUILD_TIME: " ${BUILD_TIME})

set(OPENSSL_USE_STATIC_LIBS true)

find_package(Threads REQUIRED)
#find_package(Gflags REQUIRED)
#find_package(glog REQUIRED)
find_package(OpenSSL REQUIRED)

message(STATUS "OPENSSL_VERSION:          " ${OPENSSL_VERSION})
message(STATUS "OPENSSL_INCLUDE_DIR:      " ${OPENSSL_INCLUDE_DIR})
message(STATUS "OPENSSL_CRYPTO_LIBRARY:   " ${OPENSSL_CRYPTO_LIBRARY})
message(STATUS "OPENSSL_CRYPTO_LIBRARIES: " ${OPENSSL_CRYPTO_LIBRARIES})
message(STATUS "OPENSSL_SSL_LIBRARY:      " ${OPENSSL_SSL_LIBRARY})
message(STATUS "OPENSSL_SSL_LIBRARIES:    " ${OPENSSL_SSL_LIBRARIES})
message(STATUS "OPENSSL_LIBRARIES:        " ${OPENSSL_LIBRARIES})

add_library(core STATIC OpenSSL.cpp tohex.cpp base64.cpp)

target_link_libraries(core
#    PRIVATE /usr/local/lib/libcrypto.a -lpthread
#    PRIVATE libcrypto.a
    PRIVATE ${OPENSSL_LIBRARIES}
    PRIVATE ${MATH_LIBRARY})

add_executable(main main.cpp)
target_include_directories(main
    PUBLIC ${CMAKE_SOURCE_DIR}/include
    PUBLIC ${GLOG_INCLUDE_DIRS})
target_link_libraries(main 
    PUBLIC core
#	PUBLIC libcrypto.a
	PUBLIC ${OPENSSL_LIBRARIES})
#    PUBLIC /usr/lib/x86_64-linux-gnu/libdl.a)

#add_subdirectory(src)

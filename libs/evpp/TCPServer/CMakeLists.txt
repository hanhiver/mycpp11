cmake_minimum_required (VERSION 2.8)
project (TcpTest)

set (CXX_FLAGS
         -g
         -fPIC
         -Wall
         -Wno-unused-parameter
         -Wno-unused-function
         -Wunused-variable
         -Wunused-value
         -Wshadow
         -Wcast-qual
         -Wcast-align
         -Wwrite-strings
         -Wsign-compare
         -Winvalid-pch
         -fms-extensions
         -Wfloat-equal
         -Wextra
         -std=c++11
    )

include_directories (${PROJECT_SOURCE_DIR}/..)
link_directories (/home/dhan/myprog/build/evpp/build/lib/)
link_libraries (event glog pthread evpp)
SET (EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_executable(server.out TcpServer_test1.cpp)
add_executable(client.out TcpClient_test1.cpp)

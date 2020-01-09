cmake_minimum_required(VERSION 3.4.0)

set(PROJECT_NAME "ws_engine")

# --- [ project
project(${PROJECT_NAME} C CXX)

# --- [ version
set(TARGET_VERSION "0.1.1")
set(TARGET_SOVERSION "0.1")

# --- [ Using cmake scripts and modules
#list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)

# --- [ Includes
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src
                        ${PROJECT_SOURCE_DIR}/proto)
include_directories(${PROJECT_INCLUDE_DIR}
                    ${PROJECT_BINARY_DIR})

# --- [ Dependency
include (cmake/Dependency.cmake)

if (UNIX OR APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
endif()

add_subdirectory(src)
add_subdirectory(proto)


cmake_minimum_required(VERSION 3.18)

project(hello_llvm
    VERSION 1.0.0
    LANGUAGES C CXX)

find_package(LLVM REQUIRED CONFIG)

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

llvm_map_components_to_libnames(llvm_libs support core irreader)

add_executable(hello_world hello_world.cpp)
target_link_libraries(hello_world ${llvm_libs})

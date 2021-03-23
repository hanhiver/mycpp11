cmake_minimum_required(VERSION 3.18)

project(test_uuid
    LANGUAGES CXX CUDA)

set(CUDA_USE_STATIC_CUDA_RUNTIME on)
find_package(CUDA REQUIRED)
add_library(uuid uuid.cpp)
target_include_directories(uuid 
    PUBLIC ${CUDA_INCLUDE_DIRS})
target_link_libraries(uuid 
    PUBLIC ${CUDA_LIBRARIES})

add_executable(test_uuid test_uuid.cpp)
target_link_libraries(test_uuid
    PUBLIC uuid)



add_executable(sdk_test sdk_test.cpp)

#target_include_directories(sdk_test PUBLIC ${PROTO_HDRS})
#target_include_directories(sdk_test PUBLCI ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(sdk_test PUBLIC proto_config core)
#target_link_directories(sdk_test PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/core)
target_include_directories(sdk_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/core)
target_link_directories(sdk_test PUBLIC ${CMAKE_BINARY_DIR})

add_subdirectory(core)


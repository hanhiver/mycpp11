set(LIB_BIND_HOST_SRC bind_host.cpp)

add_library(bind_host STATIC ${LIB_BIND_HOST_SRC})
target_include_directories(bind_host
    PUBLIC ${CMAKE_SOURCE_DIR}/include
    PRIVATE ${CMAKE_SOURCE_DIR}/src
    PRIVATE ${CMAKE_SOURCE_DIR}/src/cores
    PRIVATE ${CMAKE_SOURCE_DIR}/src/copenssl)
target_link_libraries(bind_host 
    PRIVATE cores
    PRIVATE copenssl
    PUBLIC proto_config
    PUBLIC ${Protobuf_LIBRARIES}
    PUBLIC Threads::Threads)

add_executable(gen_key gen_key.cpp)
target_include_directories(gen_key
    PUBLIC ${CMAKE_SOURCE_DIR}/include
    PRIVATE ${CMAKE_SOURCE_DIR}/src
    PRIVATE ${CMAKE_SOURCE_DIR}/src/cores
    PRIVATE ${CMAKE_SOURCE_DIR}/src/copenssl)
target_link_libraries(gen_key 
    PRIVATE cores
    PRIVATE copenssl
    PUBLIC Threads::Threads)
set_target_properties(gen_key
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_library(bind_host_py SHARED py_wrapper.cpp)
set_target_properties(bind_host_py PROPERTIES PREFIX "")
target_include_directories(bind_host_py
    PUBLIC ${CMAKE_SOURCE_DIR}/include
    PUBLIC Threads::Threads)

target_link_libraries(bind_host_py 
    PUBLIC bind_host
    PUBLIC Threads::Threads)

add_subdirectory(cores)
add_subdirectory(copenssl)
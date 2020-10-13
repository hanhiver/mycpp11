add_library(sdk_manager STATIC sdk_manager.cpp)

target_include_directories(sdk_manager
    PUBLIC ${CMAKE_SOURCE_DIR}/include
    PRIVATE ${CMAKE_SOURCE_DIR}/src
    PRIVATE ${CMAKE_SOURCE_DIR}/src/cores
    PRIVATE ${CMAKE_SOURCE_DIR}/src/copenssl
    PRIVATE ${CMAKE_SOURCE_DIR}/src/nlohmann
    PRIVATE ${CURL_INCLUDE_DIR})

target_link_libraries(sdk_manager 
    PRIVATE cores
    PRIVATE copenssl
    PUBLIC proto_config
    PUBLIC ${Protobuf_LIBRARIES}
    PUBLIC Threads::Threads
    PRIVATE curl)

add_subdirectory(cores)
add_subdirectory(copenssl)
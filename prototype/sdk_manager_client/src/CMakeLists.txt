set(LIB_SDK_MANAGER_SRC sdk_manager.cpp)

add_library(sdk_manager STATIC ${LIB_SDK_MANAGER_SRC})
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

#add_library(sdk_manager_static STATIC ${LIB_SDK_MANAGER_SRC})
#target_include_directories(sdk_manager_static
#    PUBLIC ${CMAKE_SOURCE_DIR}/include
#    PRIVATE ${CMAKE_SOURCE_DIR}/src
#    PRIVATE ${CMAKE_SOURCE_DIR}/src/cores
#    PRIVATE ${CMAKE_SOURCE_DIR}/src/copenssl
#    PRIVATE ${CMAKE_SOURCE_DIR}/src/nlohmann
#    PRIVATE ${CURL_INCLUDE_DIR})
#target_link_libraries(sdk_manager_static 
#    PRIVATE cores
#    PRIVATE copenssl
#    PUBLIC proto_config
#    PUBLIC ${Protobuf_LIBRARIES}
#    PUBLIC Threads::Threads
#    PRIVATE curl)
#SET_TARGET_PROPERTIES (sdk_manager_static PROPERTIES OUTPUT_NAME "sdk_manager")
#GET_TARGET_PROPERTY (OUTPUT_VALUE sdk_manager_static OUTPUT_NAME)
#SET_TARGET_PROPERTIES (sdk_manager_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
#SET_TARGET_PROPERTIES (sdk_manager PROPERTIES CLEAN_DIRECT_OUTPUT 1)

add_subdirectory(cores)
add_subdirectory(copenssl)
# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_LIB_SRCS)

# 生成链接库
add_library(cores SHARED ${DIR_LIB_SRCS})
target_link_libraries(cores 
    PUBLIC proto_config
    PUBLIC ${Protobuf_LIBRARIES})
target_compile_features(cores PUBLIC cxx_std_11)

#target_link_directories(core PUBLIC ${CMAKE_BINARY_DIR})

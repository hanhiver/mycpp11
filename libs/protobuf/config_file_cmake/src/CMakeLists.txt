
# 自动添加.目录下所有的Source文件到变量DIR_LIB_SRCS中。
#aux_source_directory(. DIR_LIB_SRCS)
# 生成链接库
#add_library(core ${DIR_LIB_SRCS})
set(CMAKE_VERBOSE_MAKEFILE ON)
#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
#INCLUDE_DIRECTORIES(${PROTO_HDRS})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
add_executable(s_test main.cpp)

target_link_libraries(s_test proto_config ${PROTOBUF_LIBRARIES})


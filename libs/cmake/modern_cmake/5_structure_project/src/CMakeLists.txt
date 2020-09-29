# 自动添加.目录下所有的Source文件到变量DIR_LIB_SRCS中。
aux_source_directory(. DIR_LIB_SRCS)
include_directories("../include/proj")
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# 生成链接库
add_library(core SHARED ${DIR_LIB_SRCS})
target_link_libraries(core proto_config)

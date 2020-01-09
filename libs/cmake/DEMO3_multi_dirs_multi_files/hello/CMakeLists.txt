# 自动添加.目录下所有的Source文件到变量DIR_LIB_SRCS中。
aux_source_directory(. DIR_LIB_SRCS)
# 生成链接库
add_library(hello ${DIR_LIB_SRCS})

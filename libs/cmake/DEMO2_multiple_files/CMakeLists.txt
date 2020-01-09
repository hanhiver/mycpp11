cmake_minimum_required(VERSION 2.8)
project(DEMO2)
#自动添加.目录下所有的Source文件到变量DIR_SRCS中。
aux_source_directory(. DIR_SRCS)
add_executable(demo2 ${DIR_SRCS})
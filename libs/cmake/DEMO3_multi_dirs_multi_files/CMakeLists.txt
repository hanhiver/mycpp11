cmake_minimum_required(VERSION 2.8)
project(DEMO2)

# 自动添加.目录下所有的Source文件到变量DIR_SRCS中。
aux_source_directory(. DIR_SRCS)

# 添加hello子目录
add_subdirectory(hello)

add_executable(demo3 main.cpp)

# 添加链接库目录
target_link_libraries(demo3 hello)
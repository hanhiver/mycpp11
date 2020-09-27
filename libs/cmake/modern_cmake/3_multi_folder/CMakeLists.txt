# 设定cmake的版本需求
cmake_minimum_required(VERSION 3.12...3.18)

# 设定项目名称，相关的说明和语言
project(1_add_executable VERSION 1.0
                         DESCRIPTION "1st example: add_executable"
                         LANGUAGES CXX)

# 设置本项目使用的c++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加hello子文件夹
add_subdirectory(hello)

# 最终生成的标的物
add_executable(a.out main.cpp)

# 设定项目的include目录
target_include_directories(hello PUBLIC hello)

# 设定输出标的物的链接库
target_link_libraries(a.out hello)
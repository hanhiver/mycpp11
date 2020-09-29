# 最终生成的标的物
add_executable(sdk_test sdk_test.cpp)

# 设定项目的include目录
target_include_directories(core PUBLIC "../src")
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# 设定输出标的物的链接库
target_link_libraries(sdk_test core proto_config)
target_include_directories(sdk_test PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
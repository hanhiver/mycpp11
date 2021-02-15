# 源代码的依赖关系为: main->hello->world
# 将world和hello分别编译为静态库，hello静态库直接连接到world静态库
# 检查对于main函数是否只需要连接hello静态库就可以。 
# g++ -c world.cpp -fPIC
# g++ -c hello.cpp -fPIC
# ar -qcs libhello.a hello.o world.o
# g++ -c main.cpp -fPIC
# g++ -o main main.o -lhello -L. 
cmake_minimum_required(VERSION 3.18)

project(main
    VERSION 1.0.0
    LANGUAGES C CXX)

#SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall -fPIC -std=c++11")

# 生成world静态库
add_library(world STATIC world.cpp)
set_property(TARGET world PROPERTY POSITION_INDEPENDENT_CODE ON)

# 生成hello静态库
add_library(hello STATIC hello.cpp)
target_link_libraries(hello 
    PRIVATE world)
set_property(TARGET hello PROPERTY POSITION_INDEPENDENT_CODE ON)
set_property(TARGET hello PROPERTY LINK_SEARCH_START_STATIC ON)

# 生成main静态程序，按道理只需要连接到hello程序库即可。
add_executable(main main.cpp)
target_link_libraries(main
    PRIVATE hello)
#    PRIVATE world)
set_property(TARGET main PROPERTY POSITION_INDEPENDENT_CODE ON)
set_property(TARGET main PROPERTY LINK_SEARCH_START_STATIC ON)

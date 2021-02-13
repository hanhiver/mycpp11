# 使用MyMath_DIR="/home/hd275562/myprog/mycpp11/CMAKE/cmake_install/build/mylib/cmake/MyMath" cmake ..
# make; make install命令完成编译安装。 
# 然后将test目录下的测试程序拷贝到build/mylib文件夹下。
# 然后在build/mylib文件夹下面建立build目录，然后cmake..; make就可以编译测试程序引用本项目中函数库。
cmake_minimum_required(VERSION 3.10)
project(install_test 
    VERSION 1.0.0
    LANGUAGES CXX)

# 如果想生成静态库，使用下面的语句。 
#add_library(mymath mymath.cc)
#target_include_directories(mymath PUBLIC ${CMAKE_SOURCE_DIR}/include)

# 如果想生成动态库，使用下面的语句。
add_library(mymath SHARED mymath.cc)
target_include_directories(mymath PRIVATE ${CMAKE_SOURCE_DIR}/include)
set_target_properties(mymath PROPERTIES PUBLIC_HEADER ${CMAKE_SOURCE_DIR}/include/mymath.h)

# 生成可执行文件 
add_executable(main mymath_main.cc)
target_link_libraries(main mymath)
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/include)

# CMAKE_INSTALL_PREFIX的默认值对于linux是/usr/local，windows就是c:\program file\
# 此处可以重新定义为自己想要的地方。 
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
install(TARGETS mymath main # 安装的目标
    EXPORT MyMath # 导出的库，可以让其他程序通过cmake引用本库的目标。
    LIBRARY DESTINATION mylib # 动态库
    ARCHIVE DESTINATION mylib # 静态库
    RUNTIME DESTINATION mylib # 可执行文件
    PUBLIC_HEADER DESTINATION mylib/include # 头文件
    )

# 写入库的版本信息
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    MyMathConfigVersion.cmake 
    VERSION ${PACKAGE_VERSION} # 当前库的版本
    COMPATIBILITY AnyNewerVersion # 向后兼容任何版本
)

# 将相应的cmake文件安装到对应的目录。
install(EXPORT MyMath
    FILE MyMath.cmake 
    NAMESPACE MyMath:: # 其他程序引用的时候可以用find_package(MyMath::mymath)来引用本项目中的mymath库。
    DESTINATION mylib/cmake/MyMath # 相关的Cmake引用文件存放的目录。 
)

# 引入对应的Config配置文件 
configure_file(MyMathConfig.cmake.in MyMathConfig.cmake @ONLY)
install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/MyMathConfig.cmake"
          "${CMAKE_CURRENT_BINARY_DIR}/MyMathConfigVersion.cmake"
    DESTINATION mylib/cmake/MyMath
)


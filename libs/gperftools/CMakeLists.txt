cmake_minimum_required(VERSION 3.8)

project(gperftools_test
    VERSION 1.0.0
    LANGUAGES CXX)

##判断操作系统类型
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free" )
    list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
    find_package(PROFILER)

    # LIBPROFILER_FOUND - If false do nnt try to use libprofiler.
    # LIBPROFILER_INCLUDE_DIRS - where to find the headfile of library.include文件夹位置
    # LIBPROFILER_LIBRARY_DIRS - where to find the libprofiler library.profiler库所在位置
    # LIBPROFILER_LIBRARIES, the library file name needed to use libprofiler.profiler库及所有依赖库列表
    # LIBPROFILER_LIBRARY - the library needed to use libprofiler. profiler库全路径

    message(STATUS "FOUND: " ${LIBPROFILER_FOUND})
    message(STATUS "INCLUDE: " ${LIBPROFILER_INCLUDE_DIRS})
    message(STATUS "LIB_DIR: " ${LIBPROFILER_LIBRARY_DIRS})
    message(STATUS "LIBRARIES: " ${LIBPROFILER_LIBRARIES})
    message(STATUS "LIBRARY: " ${LIBPROFILER_LIBRARY})

    add_executable(test simple_test.cpp)
    SET_TARGET_PROPERTIES(test PROPERTIES  LINK_FLAGS "-static-libstdc++")
    target_link_libraries(test 
        PUBLIC -pthread
        PUBLIC /usr/local/lib/libtcmalloc_and_profiler.a
        PUBLIC unwind)
    target_include_directories(test 
        PUBLIC ${LIBPROFILER_INCLUDE_DIRS})

endif(CMAKE_SYSTEM_NAME MATCHES "Linux")
# 新版本编译器要用 -pthread 而不是 -lpthread
# 否则编译时会报错找不到pthread_atfork “undefined reference to pthread_atfork”

    #######静态链接c++库###################
    #SET_TARGET_PROPERTIES(cmimpl PROPERTIES  LINK_FLAGS "-static-libstdc++")
    ###这里的参数参见我的另一篇博文 [《gcc下使用tcmalloc(gperftools)2.4的注意事项》](http://blog.csdn.net/10km/article/details/50401005)
    #set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-builtin-malloc -fno-builtin-calloc -fno-builtin-realloc -fno-builtin-free" )
    #######加入 tcmalloc 内存池支持(动态链接) #######
    #target_link_libraries(cmimpl tcmalloc_minimal)
    #message(STATUS "tcmalloc(shared) support added")
    #######linux 下加入 tcmalloc 内存池支持(静态链接) #######
    #target_link_libraries(cmimpl tcmalloc_minimal.a)
    #message(STATUS "tcmalloc(static) support added")

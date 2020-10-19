cmake_minimum_required(VERSION 3.8)
project(hello_ext
    VERSION 1.0.0
    LANGUAGES CXX)

find_package(Boost COMPONENTS python REQUIRED)
find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)

include_directories(/home/hd275562/anaconda3/envs/py38/include/python3.8)
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

MESSAGE( STATUS "Boost_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}.")
MESSAGE( STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}.")
MESSAGE( STATUS "Boost_LIB_VERSION = ${Boost_LIB_VERSION}.")

add_library(hello_ext SHARED wrapper.cpp)
# 取消生成的lib文件的lib前缀，保证python能够直接调用
set_target_properties(hello_ext PROPERTIES PREFIX "")
target_link_libraries(hello_ext 
    PUBLIC ${Boost_LIBRARIES}
    PUBLIC ${PYTHON_LIBRARIES})

#FIND_PACKAGE(Boost COMPONENTS python)
#FIND_PACKAGE(PythonInterp)
#FIND_PACKAGE(PythonLibs)
#include_directories(SYSTEM ${Boost_INCLUDE_DIR})
#include_directories(/home/hd275562/anaconda3/envs/py38/include/python3.8)

#link_libraries(${BOOST_LIBRARIES} ${PYTHON_LIBRARIES})
#add_library(hello_ext SHARED wrapper.cpp)
#set_target_properties(hello_ext PROPERTIES PREFIX "")
#target_link_libraries(hello_ext ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
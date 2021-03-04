cmake_minimum_required(VERSION 3.12)

project(boost_regex
    VERSION 1.0.0
    LANGUAGES C CXX)


set(Boost_USE_STATIC_LIBS ON) 
find_package(Boost REQUIRED COMPONENTS regex)
find_package(Threads REQUIRED)

add_executable(boost_example.out boost_example.cpp)
target_include_directories(boost_example.out
    PUBLIC ${Boost_INCLUDE_DIRS})

target_link_libraries(boost_example.out
    PUBLIC Threads::Threads
    PUBLIC ${Boost_REGEX_LIBRARY})
#    PUBLIC Boost::boost)

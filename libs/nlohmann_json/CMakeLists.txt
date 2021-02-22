cmake_minimum_required(VERSION 3.12...3.18)

project(nlohmann_json_test
    VERSION 1.0.0
    LANGUAGES CXX)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(simple_test simple_test.cpp)
add_executable(type_test type_test.cpp)
add_executable(get_ptr_test get_ptr_test.cpp)
add_executable(get_ref_test get_ref_test.cpp)
add_executable(value_type_test value_type_test.cpp)
add_executable(operators_test operators_test.cpp)
add_executable(json_list json_list.cpp)
add_executable(erase_test erase_test.cpp)
add_executable(c_python_style c_python_style.cpp)
add_executable(array_test array_test.cpp)
add_library(copenssl SHARED COpenSSL.cpp)
add_library(base64 SHARED base64.cpp)

target_link_libraries(
    copenssl PRIVATE
    base64
    ${THREADS_PREFER_PTHREAD_FLAG} 
    ${OPENSSL_CRYPTO_LIBRARIES}
    ${MATH_LIBRARY})

target_include_directories(
    base64
    PUBLIC 
    ${PROJECT_SOURCE_DIR}/copenssl/include)

target_include_directories(
    copenssl
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../copenssl/include)

set_target_properties(copenssl PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_compile_features(copenssl PUBLIC cxx_std_11)
set_target_properties(copenssl PROPERTIES CXX_EXTENSIONS OFF)

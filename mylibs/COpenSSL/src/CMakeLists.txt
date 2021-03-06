add_library(copenssl SHARED COpenSSL.cpp)
add_library(base64 SHARED base64.cpp)

target_link_libraries(
    copenssl
    PUBLIC base64
    PRIVATE ${THREADS_PREFER_PTHREAD_FLAG} 
    PRIVATE ${OPENSSL_CRYPTO_LIBRARIES}
    PRIVATE ${MATH_LIBRARY})

target_include_directories(
    base64
    PUBLIC ${PROJECT_SOURCE_DIR}/copenssl/include)

target_include_directories(
    copenssl
    PUBLIC ${PROJECT_SOURCE_DIR}/copenssl/include)

set_target_properties(
    base64 PROPERTIES 
    POSITION_INDEPENDENT_CODE ON
    CXX_EXTENSIONS OFF)

set_target_properties(
    copenssl PROPERTIES 
    POSITION_INDEPENDENT_CODE ON
    CXX_EXTENSIONS OFF)

target_compile_features(base64 PUBLIC cxx_std_11)
target_compile_features(copenssl PUBLIC cxx_std_11)

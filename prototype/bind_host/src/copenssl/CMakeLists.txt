add_library(copenssl STATIC COpenSSL.cpp)
add_library(base64 STATIC base64.cpp)

target_link_libraries(
    copenssl
    PUBLIC base64
    PRIVATE ${THREADS_PREFER_PTHREAD_FLAG} 
#    PRIVATE ${OPENSSL_CRYPTO_LIBRARIES}
    PRIVATE libcrypto.a
    PRIVATE ${MATH_LIBRARY})

#set_target_properties(
#    base64 PROPERTIES 
#    POSITION_INDEPENDENT_CODE ON
#    CXX_EXTENSIONS OFF)

#set_target_properties(
#    copenssl PROPERTIES 
#    POSITION_INDEPENDENT_CODE ON
#    CXX_EXTENSIONS OFF)

target_compile_features(base64 PUBLIC cxx_std_11)
target_compile_features(copenssl PUBLIC cxx_std_11)

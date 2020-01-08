# generate protobuf sources
file(GLOB proto_files proto/*.proto)
infer_protobuf_generate_cpp_py(${proto_gen_folder} proto_srcs proto_hdrs proto_python ${proto_files})


# include python files either to force generation
#add_library(proto STATIC ${proto_hdrs} ${proto_srcs} ${proto_python})
add_library(infer_proto ${proto_hdrs} ${proto_srcs} ${proto_python})

set(Infer_LINKER_LIBS infer_proto ${Infer_LINKER_LIBS}) # note, crucial to prepend!
infer_default_properties(infer_proto)

# creates 'test_srcs', 'srcs', 'test_cuda', 'cuda' lists
infer_pickup_infer_sources(${PROJECT_SOURCE_DIR})


# ---[ 3rdparty
include_directories(SYSTEM ${THIRDPARTY_DIR})
include_directories(SYSTEM ${THIRDPARTY_DIR}/decoder)

# ---[ Src
include_directories(common)
include_directories(core)
include_directories(preproc)
include_directories(postproc)
include_directories(platform)


if(HAVE_CUDA)
  infer_cuda_compile(cuda_objs ${cuda})
  list(APPEND srcs ${cuda_objs} ${cuda})
endif()

set(TensorRT_LINKER_LIBS /usr/local/lib/libnvcaffe_parser.so
                         /usr/local/lib/libnvonnxparser.so
                         /usr/local/lib/libnvonnxparser_runtime.so
                         /usr/local/lib/libnvinfer_plugin.so
                         /usr/local/lib/libnvinfer.so
                         /usr/local/lib/libnvparsers.so)

add_library(${PROJECT_SHORT_NAME} ${srcs})
target_link_libraries(${PROJECT_SHORT_NAME} infer_proto ${Infer_LINKER_LIBS} ${TensorRT_LINKER_LIBS})
infer_default_properties(${PROJECT_SHORT_NAME})
set_target_properties(${PROJECT_SHORT_NAME} PROPERTIES
    OUTPUT_NAME "${PROJECT_SHORT_NAME}"
    VERSION   ${INFER_TARGET_VERSION}
    SOVERSION ${INFER_TARGET_SOVERSION}

    )

# ---[ Tests
 add_subdirectory(test)

# ---[ Install
#install(DIRECTORY ${Infer_INCLUDE_DIR} DESTINATION include)
#install(FILES ${proto_hdrs} DESTINATION include/proto)
install(TARGETS ${PROJECT_SHORT_NAME} infer_proto DESTINATION lib)

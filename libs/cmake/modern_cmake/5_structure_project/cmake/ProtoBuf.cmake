# Finds Google Protocol Buffers library and compilers and extends
# the standard cmake script with version and python generation support

find_package( Protobuf REQUIRED )
include_directories(SYSTEM ${PROTOBUF_INCLUDE_DIR})
list(APPEND Infer_LINKER_LIBS ${PROTOBUF_LIBRARIES})

# As of Ubuntu 14.04 protoc is no longer a part of libprotobuf-dev package
# and should be installed separately as in: sudo apt-get install protobuf-compiler
if(EXISTS ${PROTOBUF_PROTOC_EXECUTABLE})
  message("Found PROTOBUF Compiler: ${PROTOBUF_PROTOC_EXECUTABLE}")
else()
  message(FATAL_ERROR "Could not find PROTOBUF Compiler")
endif()

if(PROTOBUF_FOUND)
  string(REGEX MATCH "([0-9])00([0-9])00([0-9])" PROTOBUF_VERSION ${GOOGLE_PROTOBUF_VERSION})
  set(PROTOBUF_VERSION "${CMAKE_MATCH_1}.${CMAKE_MATCH_2}.${CMAKE_MATCH_3}")
  unset(GOOGLE_PROTOBUF_VERSION)
endif()

# place where to generate protobuf sources
set(proto_gen_folder "${PROJECT_BINARY_DIR}/include/proto")
include_directories("${PROJECT_BINARY_DIR}/include")

set(PROTOBUF_GENERATE_CPP_APPEND_PATH TRUE)  

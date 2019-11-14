echo "Generate c++ files."
protoc -I . --grpc_out=../cpp --cpp_out=../cpp --plugin=protoc-gen-grpc=/usr/local/bin/grpc_cpp_plugin helloworld.proto
#protoc -I . --cpp_out=../cpp helloworld.proto

echo "Generate python files."
protoc -I . --python_out=../python --grpc_out=../python --plugin=protoc-gen-grpc=/usr/local/bin/grpc_python_plugin helloworld.proto




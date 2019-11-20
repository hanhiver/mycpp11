PROTOC=protoc 
CXX = g++
CPPFLAGS += `pkg-config --cflags protobuf grpc`
CXXFLAGS += -std=c++11
LDFLAGS += -L/usr/local/lib `pkg-config --libs protobuf grpc++`\
           -pthread\
           -lgrpc++_reflection\
           -ldl

all: test.pb.cc main.out 

.PRECIOUS: %.pb.cc
%.pb.cc: %.proto
	$(PROTOC) --cpp_out=. $<

main.out: main.o test.pb.o 
	$(CXX) $^ $(LDFLAGS) -o $@

clean: 
	$(RM) test.pb.cc test.pb.h

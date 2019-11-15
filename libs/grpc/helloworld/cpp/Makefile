CXX=g++
CPPFLAG += `pkg-config --cflags protobuf grpc`
CXXFLAGS += -std=c++11

LDFLAGS += -L/usr/local/lib `pkg-config --libs protobuf grpc++` \
           -lgrpc++_unsecure \
           -pthread \
		   -ldl 

all: server.out client.out 

client.out: client.o helloworld.grpc.pb.o helloworld.pb.o 
	$(CXX) $^ $(LDFLAGS) -o $@

server.out: server.o helloworld.grpc.pb.o helloworld.pb.o 
	$(CXX) $^ $(LDFLAGS) -o $@

clean:
	$(RM) *.o server.out client.out 

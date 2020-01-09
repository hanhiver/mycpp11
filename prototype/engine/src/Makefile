CXX = g++
CPPFLAGS += `pkg-config --cflags protobuf grpc`
CXXFLAGS += -std=c++11 -g
LDFLAGS += -L/usr/local/lib `pkg-config --libs protobuf grpc++`\
           -pthread -g\
           -lgrpc++_reflection\
           -ldl

all: engine.out

engine.out: engine.o config.pb.o 
	$(CXX) $^ $(LDFLAGS) -o $@

clean: 
	$(RM) test.pb.cc test.pb.h engine.out *.o

PROTOC=protoc 
CXX = g++
CPPFLAGS += `pkg-config --cflags protobuf grpc`
CXXFLAGS += -std=c++11 -g 
LDFLAGS += -L/usr/local/lib `pkg-config --libs protobuf grpc++ gflags`\
           -g\
           -pthread\
           -lgrpc++_reflection\
           -lglog\
           -ldl

all: config.pb.cc engine.out 

.PRECIOUS: %.pb.cc
%.pb.cc: ../proto/%.proto
	$(PROTOC) --cpp_out=. -I../proto $<

engine.out: engine.o config.pb.o core/params.o core/init.o
	$(CXX) $^ $(LDFLAGS) -o $@

clean: 
	$(RM) config.pb.cc config.pb.h engine.out *.o

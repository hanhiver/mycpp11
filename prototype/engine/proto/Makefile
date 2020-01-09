PROTOC=protoc 

all: config.pb.cc

.PRECIOUS: %.pb.cc
%.pb.cc: %.proto
	$(PROTOC) --cpp_out=../src $<

clean: 
	$(RM) config.pb.cc config.pb.h *.o

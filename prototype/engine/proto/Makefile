PROTOC=protoc 

all: config.pb.cc

.PRECIOUS: %.pb.cc
%.pb.cc: %.proto
	$(PROTOC) --cpp_out=. $<

clean: 
	$(RM) config.pb.cc config.pb.h

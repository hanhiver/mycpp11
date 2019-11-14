all: gflags.out

gflags.out: gflags.cpp Makefile
	g++ -o gflags.out gflags.cpp -lgflags -pthread

clean: 
	$(RM) gflags.out

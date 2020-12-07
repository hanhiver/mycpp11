CC=gcc
#CXXFLAGS=-std=c++11 -fPIC
LDFLAGS=-pthread
APPS=test1.out test2.out in_which_cpu.out 

all: $(APPS) Makefile

%.out: %.c
	$(CC) $^ -o $@ $(LDFLAGS)

.PHONY: clean 
clean:
	$(RM) $(APPS)


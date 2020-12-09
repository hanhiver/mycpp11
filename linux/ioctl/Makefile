CC=gcc
#CXXFLAGS=-std=c++11 -fPIC
LDFLAGS=-pthread
APPS=conn1.out conn2.out network.out volume.out 

all: $(APPS) Makefile

%.out: %.c
	$(CC) $^ -o $@ $(LDFLAGS)

.PHONY: clean 
clean:
	$(RM) $(APPS)


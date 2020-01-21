CC=g++
CXXFLAGS=-std=c++11 -I/usr/local/include 
LDFLAGS=-lboost_regex -lboost_regex -L/usr/local/lib
APPS=is_valid_filename_boost.out is_valid_filename.out

all: $(APPS) Makefile

%.out: %.cpp
	$(CC) $^ -o $@ $(CXXFLAGS) $(LDFLAGS)

.PHONY: clean 
clean:
	$(RM) $(APPS)

all: test

test: test.cpp Makefile
	g++ -std=c++17 -ltbb -L/usr/local/lib -o test.out test.cpp

clean:
	rm -rf test.out

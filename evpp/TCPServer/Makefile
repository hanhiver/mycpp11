CC=g++
CXXFLAGS=-std=c++11 -fPIC
LDFLAGS=-pthread -levent -lglog -levpp -L /home/dhan/myprog/build/evpp/build/lib
#APPS=TcpClient_test1.out TcpServer_test1.out
APPS=TcpClient_test1.out TcpServer_test1.out

all: $(APPS) Makefile

%.out: %.cpp
	$(CC) $^ -o $@ $(CXXFLAGS) $(LDFLAGS)

.PHONY: clean 
clean:
	$(RM) $(APPS)

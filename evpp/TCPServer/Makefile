CC=g++
CXXFLAG=-std=c++11 -pthread -levent -lglog -levpp -L /home/dhan/myprog/build/evpp/build/lib
APPS=TcpClient_test1.out TcpServer_test1.out

all: $(APPS)

%.out : %.cpp
	$(CC) $^ -o $@ $(CXXFLAG) 

#all: server.out client.out

#server.out: TcpServer_test1.cpp
#	g++ -o server.out TcpServer_test1.cpp -pthread -levent -lglog -levpp -I .. -L /home/dhan/myprog/build/evpp/build/lib

#client.out: TcpClient_test1.cpp 
#	g++ -o client.out TcpClient_test1.cpp -pthread -levent -lglog -levpp -I .. -L /home/dhan/myprog/build/evpp/build/lib

clean:
	rm -rf $(APPS)

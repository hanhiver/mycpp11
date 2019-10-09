all: test.out

test.out: event_loop.cpp
	g++ -o test.out event_loop.cpp -pthread -levent -lglog -levpp -I .. -L /home/dhan/myprog/build/evpp/build/lib

clean:
	rm -rf test.out

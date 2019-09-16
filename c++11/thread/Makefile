CPP_APPS=test1 test2 test3 test4

CPP_ARGS=
CPP_LIBS=-lpthread

all:  $(CPP_APPS)


%: %.cpp
	g++ $(CPP_ARGS) -o $@ $< $(CPP_LIBS) 

clean:
	rm -rf $(CPP_APPS)




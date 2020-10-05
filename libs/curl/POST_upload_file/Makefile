APPS=upload_file_POST.out
#ARGS=$(shell pkg-config --cflags --libs opencv)
ARGS=--std=c++11 -pthread -lcurl -lssl -lcrypto -ldl 
#  g++  -O2 -Wall -Wno-write-strings  -D_LINUX  -L../libcurl/lib -I../libcurl/include  -std=c++11  ./test_main.cpp   -L../libcurl/lib -lcurl -lssl -lcrypto  -ldl -pthread -o sample_X86_64

all: $(APPS)

%.out: %.cpp
	@echo "Compile the cpp files."
	g++ $< -o $@ $(ARGS)

.PHONY: clean
clean:
	@echo "Clean the project."
	-rm -rf $(APPS)


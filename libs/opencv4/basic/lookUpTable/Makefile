APPS=lut.out
ARGS=$(shell pkg-config --cflags --libs opencv4)
CXXFLAGS=-std=c++11 -lm -lpthread

all: $(APPS)

%.out: %.cpp
	@echo "Compile the cpp files."
	g++ -o $@ $< $(ARGS)

.PHONY: clean
clean:
	@echo "Clean the project."
	-rm -rf $(APPS)



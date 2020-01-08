APPS=parallel_for.out
ARGS=$(shell pkg-config --cflags --libs opencv4) -std=c++11

all: $(APPS)

%.out: %.cpp
	@echo "Compile the cpp files."
	g++ -o $@ $< $(ARGS)

.PHONY: clean
clean:
	@echo "Clean the project."
	-rm -rf $(APPS)



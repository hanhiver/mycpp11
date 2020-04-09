APPS=surf.out surf_gpu.out surf_bench.out surf_bench2.out
ARGS=$(shell pkg-config --cflags --libs opencv4) -std=c++17

all: $(APPS)

%.out: %.cpp
	@echo "Compile the cpp files."
	g++ -o $@ $< $(ARGS) -pthread

.PHONY: clean
clean:
	@echo "Clean the project."
	-rm -rf $(APPS)


APPS=surf.out surf_gpu.out
ARGS=$(shell pkg-config --cflags --libs opencv4)

all: $(APPS)

%.out: %.cpp
	@echo "Compile the cpp files."
	g++ -o $@ $< $(ARGS)

.PHONY: clean
clean:
	@echo "Clean the project."
	-rm -rf $(APPS)


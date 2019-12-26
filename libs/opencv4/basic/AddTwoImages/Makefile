APPS=add2imgs.out contrast_brightness.out
ARGS=$(shell pkg-config --cflags --libs opencv4)

all: $(APPS)

%.out: %.cpp
	@echo "Compile the cpp files."
	g++ -std=c++11 -o $@ $< $(ARGS)

.PHONY: clean
clean:
	@echo "Clean the project."
	-rm -rf $(APPS)



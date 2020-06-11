APPS=example.out histogram.out
ARGS=-lprometheus-cpp-pull -lprometheus-cpp-core -std=c++11

all: $(APPS)

%.out: %.cpp
	@echo "Compile the cpp files."
	g++ -o $@ $< $(ARGS) -pthread

.PHONY: clean
clean:
	@echo "Clean the project."
	-rm -rf $(APPS)


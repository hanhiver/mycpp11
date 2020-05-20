APPS=example.out histogram.out
ARGS=-lprometheus-cpp-pull -lprometheus-cpp-core -lz -std=c++17

all: $(APPS)

%.out: %.cpp
	@echo "Compile the cpp files."
	g++ -o $@ $< $(ARGS) -pthread

.PHONY: clean
clean:
	@echo "Clean the project."
	-rm -rf $(APPS)


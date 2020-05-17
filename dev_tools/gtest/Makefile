APPS=first_example.out assert_test.out GlobalTest.out map_test.out dead_test.out general_test.out
ARGS=$(shell pkg-config --cflags --libs gtest) -std=c++11

all: $(APPS)

%.out: %.cpp
	@echo "Compile the cpp files."
	g++ -o $@ $< $(ARGS) -pthread

.PHONY: clean
clean:
	@echo "Clean the project."
	-rm -rf $(APPS)


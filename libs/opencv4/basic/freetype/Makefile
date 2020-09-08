APPS=main.out
ARGS=$(shell pkg-config --cflags --libs opencv4,freetype2) -std=c++11 -lm -lpthread

all: $(APPS)

%.o: %.cpp
	$(CC) $(INCLUDES) $(DEBUG) -c $(CFLAGS) $< -o $@

%.out: %.o
	@echo "Compile the cpp files."
	g++ -o $@ $< $(ARGS)

.PHONY: clean
clean:
	@echo "Clean the project."
	-rm -rf $(APPS)



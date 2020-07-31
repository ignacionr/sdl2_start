CXXFLAGS=-std=c++14
LDFLAGS=-lSDL2 -lSDL2_image
CXXFLAGS=-std=c++14

test: test.o
	$(CXX) test.o -o test $(LDFLAGS)

run: test
	./test

clean:
	rm test *.o

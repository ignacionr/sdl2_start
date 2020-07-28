CXXFLAGS=-std=c++14
LDFLAGS=-lSDL2 -lSDL2_image

test: test.o
	$(CXX) test.o -o test $(LDFLAGS)

run: test
	./test

clean:
	rm test *.o

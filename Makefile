CXXFLAGS=-std=c++17
LDFLAGS=-lSDL2 -lSDL2_image

test: test.o
	$(CXX) test.o -o test $(LDFLAGS)

run: test
	./test

clean:
	rm test *.o

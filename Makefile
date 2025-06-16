#mishaaskarov@gmail.com

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -g
LDFLAGS =

all: main

main: Demo.cpp MyContainer.hpp 
	$(CXX) $(CXXFLAGS) -o main Demo.cpp

test: Test.cpp MyContainer.hpp
	$(CXX) $(CXXFLAGS) -o Test Test.cpp
	./Test

valgrind: test
	valgrind --leak-check=full ./Test

clean:
	rm -f main Test *.o *.out

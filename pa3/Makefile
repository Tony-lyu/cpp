CXX = g++
CXXFLAGS = -std=c++11
all: main
main: main.o
	$(CXX) $(CXXFLAGS) -o main main.o
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp
clean:
	rm -f *.o main

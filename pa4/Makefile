CXX = g++

CXXFLAGS = -Wall -std=c++11

TARGET = main


all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp


run: $(TARGET)
	./$(TARGET)


clean:
	rm -f $(TARGET)

.PHONY: all run clean

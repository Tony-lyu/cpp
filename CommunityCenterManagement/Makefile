CXX = g++
CXXFLAGS = -Wall -std=c++11

EXEC = main

SOURCES = main.cpp center.cpp event_user.cpp event.cpp user.cpp pay.cpp

OBJECTS = $(SOURCES:.cpp=.o)

DEPS = center.h event_user.h event.h user.h pay.h

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJECTS) $(EXEC)

main.o: center.h event.h user.h event_user.h pay.h
center.o: center.h event.h user.h event_user.h
event_user.o: event_user.h
event.o: event.h user.h
user.o: user.h event.h
pay.o: pay.h

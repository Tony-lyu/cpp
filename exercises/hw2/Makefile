CXX = g++

CXXFLAGS = -Wall -g -std=c++11

INCLUDES =

LFLAGS =

SRCS = main.cpp flight.cpp

OBJS = $(SRCS:.cpp=.o)

MAIN = flightSystem

.PHONY: depend clean

all:    $(MAIN)
	@echo  run flightSystem for main

$(MAIN): $(OBJS) 
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS)

.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN)
	rm -f flightSystem

depend: $(SRCS)
	makedepend $(INCLUDES) $^

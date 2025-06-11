# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -g

# Source files and object files
SRCS = Specie.cpp WorkerAnt.cpp Ant.cpp Doodlebug.cpp Grid.cpp MaleAnt.cpp Position.cpp QueenAnt.cpp Simulation.cpp
OBJS = $(SRCS:.cpp=.o) driver.o

# Executable name
EXEC = simulation

# Default target
all: $(EXEC)

# Link the object files with driver.o into the final executable
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Special rule for driver.cpp since it's the main program file
driver.o: driver.cpp
	$(CXX) $(CXXFLAGS) -c driver.cpp

# Clean target
clean:
	rm -f $(OBJS) $(EXEC)

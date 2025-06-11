#pragma once
#include "Grid.h"
#include <vector>

using namespace std;
class Simulation
{
private:
	Grid grid;
	void initialize_grid(int numQueens, int numDoodlebugs, int numWorkers, int numMales);
	
public:

	Simulation(int numQueens, int numDoodlebugs, int numWorkers, int numMales);
	void simulate();
	void displayGrid() const;
};


#pragma once
#include "Specie.h"
#include "Grid.h"
#include <algorithm>
class Doodlebug: public Specie
{
private:
	int lastMoveIndex;
	int timeSinceLastBreed;
	int timeSinceLastEat;
public:
	Doodlebug(int x, int y);
	void randomMove(Grid& grid) override;
	void breed(Grid& grid);
	string toString() override;
	// Inherited via Specie
	bool checkStarving() override;
};


#pragma once
#include "Position.h"
#include <string>
class Grid;
using namespace std;

class Specie
{
protected:
	Position position;
public:
	Specie(int x, int y);
	virtual void randomMove(Grid& grid) = 0;
	virtual string toString() = 0;
	virtual bool checkStarving() = 0;
	Position getPosition();
};


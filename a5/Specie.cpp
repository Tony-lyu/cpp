#include "Specie.h"

Specie::Specie(int x, int y)
{
	position.setPosition(x, y);
}

Position Specie::getPosition()
{
	return position;
}

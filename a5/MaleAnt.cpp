#include "MaleAnt.h"

MaleAnt::MaleAnt(int x, int y): Ant(x, y)
{
}

void MaleAnt::randomMove(Grid& grid)
{
    Ant::randomMove(grid);
}

string MaleAnt::toString()
{
    return "male_ant";
}

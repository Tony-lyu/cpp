#include "WorkerAnt.h"

WorkerAnt::WorkerAnt(int x, int y): Ant(x, y)
{
}

void WorkerAnt::randomMove(Grid& grid)
{
    Ant::randomMove(grid);
}

string WorkerAnt::toString()
{
    return "worker_ant";
}

#pragma once
#include "Ant.h"
class WorkerAnt :
    public Ant
{
public:
    WorkerAnt(int x, int y);
    // Inherited via Ant
    void randomMove(Grid& grid) override;
    string toString() override;
};


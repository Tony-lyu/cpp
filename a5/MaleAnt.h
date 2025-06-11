#pragma once
#include "MaleAnt.h"
#include "Ant.h"
#include "Simulation.h"
#include "Specie.h"
#include "Grid.h"

class MaleAnt : public Ant
{
public:
    MaleAnt(int x, int y);
    void randomMove(Grid& grid) override;
    string toString() override;
};


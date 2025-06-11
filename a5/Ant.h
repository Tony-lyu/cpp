#pragma once
#include "Specie.h"
class Ant : public Specie
{
private:
    int stay_time;
public:
    Ant(int x, int y);
    // Inherited via Specie
    void randomMove(Grid& grid) override;
    bool checkStarving();

    // Inherited via Specie
    string toString() override;
};


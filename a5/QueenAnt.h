#pragma once
#include "Ant.h"
#include "MaleAnt.h"
#include "WorkerAnt.h"
class QueenAnt :
    public Ant
{
private:
    bool isMated;
    int timeSinceMated;
    int timeSinceLastBreed;
    bool isCataglyphisQueen;
    bool isFirstMate;

public:
    QueenAnt(int x, int y, bool isCataglyphisQueen = false);
    void randomMove(Grid& grid) override;
    int breed(Grid& grid);
    string toString() override;
    void checkIfMated(Grid& grid);
};


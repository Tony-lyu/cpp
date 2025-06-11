#pragma once
#include "Specie.h"
#include <vector>

using namespace std;

class Grid
{
private:
    Specie** cells; // 2D array of pointers to Specie objects
    int dims; // Dimensions of the grid

public:
    void killSpecie(int x, int y);
    bool AddSpecie(Specie* specie, int x, int y);
    Grid(int dimensions); // Constructor
    ~Grid(); // Destructor to handle memory cleanup
    int getDims() const;
    void setItemAt(int x, int y, Specie* item);
    Specie* getItemAt(int x, int y) const;
    bool moveItem(int fromX, int fromY, int toX, int toY);
    bool isValidMove(int x, int y) const;
    void simulateStep();
};

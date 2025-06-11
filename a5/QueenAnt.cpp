#include "QueenAnt.h"

QueenAnt::QueenAnt(int x, int y, bool isCataglyphisQueen): Ant(x, y)
{
    this->isMated = false;
    this->timeSinceMated = 0;
    this->timeSinceLastBreed = 0;
    this->isCataglyphisQueen = isCataglyphisQueen;
    this->isFirstMate = true;
}

void QueenAnt::randomMove(Grid& grid)
{
    if (isMated == false)
    {
        Ant::randomMove(grid);
        checkIfMated(grid);
    }
    else
    {
        this->timeSinceMated++;
        this->timeSinceLastBreed++;
        
    }

    breed(grid);
}

int QueenAnt::breed(Grid& grid)
{
    if ((isMated || isCataglyphisQueen) && timeSinceMated >= 30 && timeSinceLastBreed >= 30)
    {
        // Define the 16-neighborhood (including the 8 adjacent cells and the outer ring)
        int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1, -2, -2, -2, 0, 2, 2, 2, 0 };
        int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1, -2, 0, 2, -2, -2, 0, 2, 2 };

        int offspringCount = 0;

        for (int i = 0; i < 16 && offspringCount < 10; ++i)  // Limit offspring to 10
        {
            int newX = position.getX() + dx[i];
            int newY = position.getY() + dy[i];

            // Check if the new position is within the grid and the cell is empty
            if (grid.isValidMove(newX, newY) && grid.getItemAt(newX, newY) == nullptr)
            {
                double rnd = static_cast<double>(rand()) / RAND_MAX; // Random number between 0 and 1

                Specie* newAnt = nullptr;
                if (rnd < 0.005)
                { // 0.5% chance for a new queen
                    newAnt = new QueenAnt(newX, newY);
                }
                else if (rnd < 0.0105)
                { // Additional 0.01% chance for a cataglyphis queen
                    newAnt = new QueenAnt(newX, newY, true); 
                }
                else if (rnd < 0.5)
                { // 40% chance for a male ant, cumulative 50%
                    newAnt = new MaleAnt(newX, newY);
                }
                else
                { // Remaining 50-90% chance for a worker ant
                    newAnt = new WorkerAnt(newX, newY);
                }

                // Add the new ant to the simulation
                grid.AddSpecie(newAnt, newX, newY);
                
                offspringCount++;
            }
        }

        if (offspringCount > 0)
        {
            // Reset the time since last breed counter if any offspring were produced
            timeSinceLastBreed = 0;
            isMated = false;
            timeSinceMated = 0;
            return 1;
        }
        // If no offspring were produced and it's been 90 time steps since last successful breed, the queen dies
        else if (timeSinceLastBreed >= 90)
        {
            // Implement queen's death (e.g., removing from the grid)
            return -1;

        }
    }


    if (timeSinceLastBreed < 90) timeSinceLastBreed++;  // Cap at 90 to avoid overflo
    return 0;
}

string QueenAnt::toString()
{
    return "queen_ant";
}

void QueenAnt::checkIfMated(Grid& grid)
{
    if (timeSinceLastBreed < 30 && isFirstMate == false)
    {
        return;
    }
    // Define the search area for mating partners (adjacent cells)
    int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    for (int i = 0; i < 8; ++i) // Check all 8 surrounding cells
    {
        int newX = position.getX() + dx[i];
        int newY = position.getY() + dy[i];

        if (grid.isValidMove(newX, newY)) // Check if the adjacent cell is within grid bounds
        {
            Specie* specie = grid.getItemAt(newX, newY);
            if (specie && specie->toString() == "male_ant") // Check if there's a male ant in the adjacent cell
            {
                isMated = true;
                isFirstMate = false;
                break; // Stop searching once a mate is found
            }
        }
    }
}
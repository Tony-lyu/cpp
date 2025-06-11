#include "Simulation.h"
#include "QueenAnt.h"
#include "MaleAnt.h"
#include "Doodlebug.h"
#include "WorkerAnt.h"

Simulation::Simulation(int numQueens, int numDoodlebugs, int numWorkers, int numMales) : grid(numDoodlebugs + numQueens + numWorkers + numMales)
{
    srand(static_cast<unsigned>(time(nullptr))); // Seed the random number generator

    initialize_grid(numQueens, numDoodlebugs, numWorkers, numMales);
}

void Simulation::initialize_grid(int numQueens, int numDoodlebugs, int numWorkers, int numMales)
{

    // Example of placing a QueenAnt on the grid
    int placings = 0;

    while (placings != numQueens)
    {
        int x = rand() % grid.getDims();
        int y = rand() % grid.getDims();
        if (grid.getItemAt(x, y) == nullptr)
        {
            QueenAnt* queen = new QueenAnt(x, y);
            grid.setItemAt(x, y, queen);
            placings++;
        }
    }

    placings = 0;
    while (placings != numMales)
    {
        int x = rand() % grid.getDims();
        int y = rand() % grid.getDims();
        if (grid.getItemAt(x, y) == nullptr)
        {
            MaleAnt* maleAnt = new MaleAnt(x, y);
            grid.setItemAt(x, y, maleAnt);
            placings++;
        }
    }

    placings = 0;
    while (placings != numDoodlebugs)
    {
        int x = rand() % grid.getDims();
        int y = rand() % grid.getDims();
        if (grid.getItemAt(x, y) == nullptr)
        {
            Doodlebug* doodlebug = new Doodlebug(x, y);
            grid.setItemAt(x, y, doodlebug);
            placings++;
        }
    }

    placings = 0;
    while (placings != numWorkers)
    {
        int x = rand() % grid.getDims();
        int y = rand() % grid.getDims();
        if (grid.getItemAt(x, y) == nullptr)
        {
            WorkerAnt* workerAnt = new WorkerAnt(x, y);
            grid.setItemAt(x, y, workerAnt);
            placings++;
        }
    }
}

void Simulation::displayGrid() const
{
    for (int y = 0; y < grid.getDims(); ++y) { // Assuming grid has getHeight method
        for (int x = 0; x < grid.getDims(); ++x) { // Assuming grid has getWidth method
            Specie* specie = grid.getItemAt(x, y); // Assuming getItemAt returns a Specie pointer
            if (specie != nullptr) {
                std::string specieType = specie->toString();
                if (specieType == "queen_ant") {
                    std::cout << 'Q';
                }
                else if (specieType == "worker_ant") {
                    std::cout << 'w';
                }
                else if (specieType == "male_ant") {
                    std::cout << 'o';
                }
                else if (specieType == "doodlebug") {
                    std::cout << 'X';
                }
                else {
                    std::cout << '?'; // Unknown specie
                }
            }
            else {
                std::cout << '.'; // Empty cell
            }
        }
        std::cout << std::endl; // New line at the end of each row
    }
    std::cout << "\n";
}

void Simulation::simulate()
{
    int timeStamp = 0;
    while (timeStamp < 100)
    {
        displayGrid();
        grid.simulateStep();
        timeStamp++;
    }
}


#include "Simulation.h"
int main()
{
    int numQueens, numDoodlebugs, numWorkers, numMales;

    std::cout << "Enter the number of Queen Ants: ";
    std::cin >> numQueens;

    std::cout << "Enter the number of Doodlebugs: ";
    std::cin >> numDoodlebugs;

    std::cout << "Enter the number of Worker Ants: ";
    std::cin >> numWorkers;

    std::cout << "Enter the number of Male Ants: ";
    std::cin >> numMales;
	Simulation simulation(numQueens, numDoodlebugs, numWorkers, numMales);
	simulation.simulate();
	return 0;
}
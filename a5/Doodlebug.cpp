#include "Doodlebug.h"

bool endsWith(const std::string& fullString, const std::string& ending)
{
    if (fullString.length() >= ending.length())
    {
        return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
    }
    else
    {
        return false;
    }
}

Doodlebug::Doodlebug(int x, int y): Specie(x, y)
{
    this->lastMoveIndex = 0;
    this->timeSinceLastEat = 0;
    this->timeSinceLastBreed = 0;
}

void Doodlebug::randomMove(Grid& grid)
{
    // Define the clockwise moves: up, right, down, left, and diagonals (up-right, down-right, down-left, up-left)
    int dx[8] = { 0, 1, 0, -1, 1, 1, -1, -1 };
    int dy[8] = { -1, 0, 1, 0, -1, 1, 1, -1 };

    // Assuming lastMoveIndex stores the index of the last move direction, initialized to -1 initially
    int moveIndex = (lastMoveIndex + 1) % 8; // Move in the next clockwise direction
    int newX = position.getX();
    int newY = position.getY();
    // First, check for adjacent ants to eat
    bool antFound = false;
    for (int i = 0; i < 8; ++i)
    {
        int checkX = position.getX() + dx[i];
        int checkY = position.getY() + dy[i];
        if (grid.isValidMove(checkX, checkY) && grid.getItemAt(checkX, checkY) != nullptr && endsWith(grid.getItemAt(checkX, checkY)->toString(), "ant"))
        {
            newX = checkX;
            newY = checkY;
            antFound = true;
            break;
        }
    }

    // If no ant is found, attempt the clockwise move
    if (!antFound)
    {
        newX = position.getX() + dx[moveIndex];
        newY = position.getY() + dy[moveIndex];

        if (!grid.isValidMove(newX, newY))
        {
            // If hitting a wall, reverse direction (bounce)
            newX = position.getX() - dx[moveIndex];
            newY = position.getY() - dy[moveIndex];

            // Check if the bounce is valid and the cell is unoccupied
            if (!grid.isValidMove(newX, newY) || grid.getItemAt(newX, newY) != nullptr) {
                // If bouncing back is invalid or the cell is occupied, stay in place
                newX = position.getX();
                newY = position.getY();
            }
        }
        else if (grid.getItemAt(newX, newY) != nullptr)
        {
            // If the intended cell is occupied, stay in place
            newX = position.getX();
            newY = position.getY();
        }
    }
    // Move the doodlebug if the new position is different from the current position
    if (newX != position.getX() || newY != position.getY())
    {
        // If moving to a cell with an ant, simulate eating the ant
        if (antFound)
        {
            grid.killSpecie(newX, newY);
            timeSinceLastEat = 0;
        }

        grid.moveItem(position.getX(), position.getY(), newX, newY);
        position.setPosition(newX, newY);
        lastMoveIndex = moveIndex; // Update the last move direction
    }
    timeSinceLastEat++;
    breed(grid);
}

void Doodlebug::breed(Grid& grid)
{
    if (timeSinceLastBreed >= 10) // Check if it's time to breed
    {
        // Define the 16-neighborhood (including the 8 adjacent cells and the outer ring)
        int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1, -2, -2, -2, 0, 2, 2, 2, 0 };
        int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1, -2, 0, 2, -2, -2, 0, 2, 2 };

        bool spawned = false;

        // Shuffle the order of the neighborhood indices to randomize offspring placement
        std::vector<int> indices = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

        std::random_shuffle(indices.begin(), indices.end()); // Shuffle the indices

        for (int index : indices)  // Iterate through shuffled indices
        {
            int newX = position.getX() + dx[index];
            int newY = position.getY() + dy[index];

            // Check if the new position is within the grid and the cell is empty
            if (grid.isValidMove(newX, newY) && grid.getItemAt(newX, newY) == nullptr)
            {
                Doodlebug* newDoodlebug = new Doodlebug(newX, newY);

                // Add the new doodlebug to the simulation
                grid.AddSpecie(newDoodlebug, newX, newY);

                spawned = true;
                break; // Stop after spawning one doodlebug
            }
        }

        // Reset the breeding timer after attempting to breed

        timeSinceLastBreed = -1;

    }

    // Increment the time since last breed
    timeSinceLastBreed++;
}


string Doodlebug::toString()
{
    return "doodlebug";
}

bool Doodlebug::checkStarving()
{
    return timeSinceLastEat >= 20;
}
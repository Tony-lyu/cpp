#include "Ant.h"
#include "Grid.h"

Ant::Ant(int x, int y): Specie(x, y)
{
    this->stay_time = 0;
}

void Ant::randomMove(Grid& grid)
{
    // Define the possible moves: up, down, left, right, and diagonals
    int dx[8] = { 0, 0, -1, 1, -1, 1, -1, 1 };
    int dy[8] = { -1, 1, 0, 0, -1, -1, 1, 1 };

    // Randomly select one of the eight possible moves
    int moveIndex = rand() % 8;
    int newX = position.getX() + dx[moveIndex];
    int newY = position.getY() + dy[moveIndex];

    if (!grid.isValidMove(newX, newY))
    {
        // Bounce back: Reverse the direction
        int bounceX = position.getX() - dx[moveIndex];
        int bounceY = position.getY() - dy[moveIndex];

        // Check if the bounce is valid and the cell is unoccupied
        if (grid.isValidMove(bounceX, bounceY) && grid.getItemAt(bounceX, bounceY) == nullptr)
        {
            newX = bounceX;
            newY = bounceY;
        }
        else
        {
            // If bouncing back hits a wall or is occupied, try moving twice in the original direction if possible
            newX += dx[moveIndex];
            newY += dy[moveIndex];
            if (!grid.isValidMove(newX, newY) || grid.getItemAt(newX, newY) != nullptr)
            {
                // Stay in place if the second move is also invalid or the cell is occupied
                newX = position.getX();
                newY = position.getY();
            }
        }
    }
    else if (grid.getItemAt(newX, newY) != nullptr)
    {
        // If the cell in the intended direction is occupied, stay in place
        newX = position.getX();
        newY = position.getY();
    }

    // Move the ant if the new position is different from the current position
    if (newX != position.getX() || newY != position.getY())
    {
        grid.moveItem(position.getX(), position.getY(), newX, newY);
        position.setPosition(newX, newY);
        stay_time = 0;
    }
    else
    {
        stay_time++;
    }
}

bool Ant::checkStarving()
{
    return stay_time >= 5;
}

string Ant::toString()
{
    return "ant";
}

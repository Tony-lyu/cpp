#include "Grid.h"
#include <iostream>

Grid::Grid(int dimensions) : dims(dimensions)
{
    cells = new Specie * [dims * dims]; // Allocate array of row pointers
    for (int i = 0; i < dims; ++i)
    {
        for (int j = 0; j < dims; j++)
        {
            cells[i * dims + j] = nullptr; // Allocate each row and initialize to nullptr
        }
    }
}


Grid::~Grid()
{
    for (int i = 0; i < dims; ++i)
    {
        for (int j = 0; j < dims; j++)
        {
            if (cells[i * dims + j] != nullptr)
                delete cells[i * dims + j];
            cells[i * dims + j] = nullptr; // Allocate each row and initialize to nullptr
        }
    }
    // Delete the array of pointers
    delete[] cells;
}

int Grid::getDims() const
{
    return this->dims;
}

void Grid::setItemAt(int x, int y, Specie* item)
{
    if (isValidMove(x, y))
    {
        if (cells[x * dims + y] != nullptr)
            delete cells[x * dims + y]; // Clean up the existing specie if any
        cells[x * dims + y] = item; // Set the new Specie at the specified location
    }
}

Specie* Grid::getItemAt(int x, int y) const
{
    if (isValidMove(x, y))
    {
        return cells[x * dims + y];
    }
    return nullptr; // Return nullptr if the coordinates are out of bounds
}


void Grid::killSpecie(int x, int y)
{

    if (isValidMove(x, y) && getItemAt(x, y) != nullptr)
    {
        setItemAt(x, y, nullptr);
    }
}

bool Grid::AddSpecie(Specie* specie, int x, int y)
{

    if (isValidMove(x, y) && getItemAt(x, y) == nullptr)
    {
        setItemAt(x, y, specie);
        return true;
    }

    return false;
}


bool Grid::moveItem(int fromX, int fromY, int toX, int toY)
{
    if (isValidMove(fromX, fromY) && isValidMove(toX, toY) && cells[fromX * dims + fromY] != nullptr)
    {
        // Move the Specie to the new location and clear the old location
        cells[toX * dims + toY] = cells[fromX * dims + fromY];
        cells[fromX * dims + fromY] = nullptr;
        return true;
    }
    return false; // Move was not possible
}

bool Grid::isValidMove(int x, int y) const
{
    // Check if the given coordinates are within the grid bounds
    return x >= 0 && y >= 0 && x < dims && y < dims;
}

void Grid::simulateStep()
{

    for (int i = 0; i < dims; i++)
    {
        for (int j = 0; j < dims; j++)
        {
            if (cells[i * dims + j] != nullptr && cells[i * dims + j]->toString() == "doodlebug")
            {
                Specie* dbug = cells[i * dims + j];
                dbug->randomMove(*this);
                if (dbug->checkStarving() == true)
                {
                    this->killSpecie(dbug->getPosition().getX(), dbug->getPosition().getY());
                }
            }
        }
    }

    for (int i = 0; i < dims; i++)
    {
        for (int j = 0; j < dims; j++)
        {
            if (cells[i * dims + j] != nullptr && cells[i * dims + j]->toString() == "queen_ant")
            {
                Specie* queen_ant = cells[i * dims + j];
                queen_ant->randomMove(*this);
            }
        }
    }

    for (int i = 0; i < dims; i++)
    {
        for (int j = 0; j < dims; j++)
        {
            if (cells[i * dims + j] != nullptr && cells[i * dims + j]->toString() != "queen_ant" && cells[i * dims + j]->toString() != "doodlebug")
            {
                
                Specie* ant = cells[i * dims + j];
                ant->randomMove(*this);
                if (ant->checkStarving() == true)
                {
                    this->killSpecie(ant->getPosition().getX(), ant->getPosition().getY());
                }
            }
        }
    }

}

#include "Position.h"

// Default constructor
Position::Position() : x(0), y(0) {}

// Parameterized constructor
Position::Position(int xVal, int yVal) : x(xVal), y(yVal) {}

void Position::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Position::getX()
{
    return this->x;
}

int Position::getY()
{
    return this->y;
}

// Copy constructor
Position::Position(const Position& pos) : x(pos.x), y(pos.y) {}

// Assignment operator
Position& Position::operator=(const Position& pos)
{
    if (this != &pos) {
        x = pos.x;
        y = pos.y;
    }
    return *this;
}

// Equality operator
bool Position::operator==(const Position& other) const
{
    return x == other.x && y == other.y;
}


// Move position by dx and dy
void Position::move(int dx, int dy)
{
    x += dx;
    y += dy;
}

// Display the position
void Position::display() const
{
    std::cout << "Position: (" << x << ", " << y << ")" << std::endl;
}
#pragma once
#include <iostream>

class Position
{
private:
    int x; // X-coordinate
    int y; // Y-coordinate
public:
    

    // Constructors
    Position();
    Position(int x, int y);

    void setPosition(int x, int y);

    int getX();

    int getY();

    // Copy constructor
    Position(const Position& other);

    // Assignment operator
    Position& operator=(const Position& other);

    // Equality operators
    bool operator==(const Position& other) const;

    // Movement method
    void move(int dx, int dy);

    // Display method
    void display() const;
};


#include "Position.hpp"

Position::Position() {}

Position::Position(int coords[4][2])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            this->coords[i][j] = coords[i][j];
        }
    }
}

// this is a deep copy
Position& Position::operator=(Position right)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            coords[i][j] = right.get(i, j);
        }
    }

    return *this;
}


int Position::get(int x, int y)
{
    return coords[x][y];
}

void Position::set(int x, int y, int val)
{
    coords[x][y] = val;
}

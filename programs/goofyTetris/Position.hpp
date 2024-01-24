#pragma once

class Position {
    private:
        const int coordCount = 4;
        const int dimCount = 2;
        int coords[4][2];
    public:
        Position();
        Position(int coords[4][2]);
        Position& operator=(Position right);

        int get(int x, int y);
};
#pragma once
#include "enums.hpp"

class GameState {
    private:
        SquareContent playingField[10*24];
    public:
        GameState();
        SquareContent getFieldSquare(int x, int y);
};

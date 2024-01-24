#pragma once
#include "enums.hpp"

class GameState {
    private:
    public:
        const int lockDelay = 50;
        const int framesPerLine = 100;
        int lockDelayTimer = 0;
        int frameCount = 0;
        int secondCount = 0;
        bool softDropping = false;
        bool justSetDown = true;
        int score = 0;
        SquareContent playingField[10][24];

        GameState();
};

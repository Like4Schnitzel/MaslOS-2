#include "GameState.hpp"

GameState::GameState()
{
    for (int i = 0; i < 240; i++)
    {
        playingField[i] = SquareContent::EMPTY;
    }
}

#include "GameState.hpp"

GameState::GameState()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 24; j++)
        {
            playingField[i][j] = SquareContent::Empty;
        }
    }
}

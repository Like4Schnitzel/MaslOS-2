#include "Tetromino.hpp"

Tetromino::Tetromino(Shape shape)
{
    rotationState = 0;
    color = ShapeToRGB(shape);

    switch (shape)
    {
        case Shape::O: 
        {
            position = Position((int[4][2]) {
                { 4, 21 },
                { 5, 21 },
                { 4, 20 },
                { 5, 20 }
            });
            break;
        }

        case Shape::I: 
        {
            position = Position((int[4][2]) {
                { 6, 20 },
                { 5, 20 },
                { 4, 20 },
                { 3, 20 }
            });
            break;
        }

        case Shape::J: 
        {
            position = Position((int[4][2]) {
                { 3, 21 },
                { 3, 20 },
                { 4, 20 },
                { 5, 20 }
            });
            break;
        }

        case Shape::L: 
        {
            position = Position((int[4][2]) {
                { 5, 21 },
                { 3, 20 },
                { 4, 20 },
                { 5, 20 }
            });
            break;
        }

        case Shape::S: 
        {
            position = Position((int[4][2]) {
                { 4, 21 },
                { 5, 21 },
                { 4, 20 },
                { 3, 20 }
            });
            break;
        }

        case Shape::Z: 
        {
            position = Position((int[4][2]) {
                { 3, 21 },
                { 4, 21 },
                { 4, 20 },
                { 5, 20 }
            });
            break;
        }

        case Shape::T:
        {
            position = Position((int[4][2]) {
                { 4, 21 },
                { 3, 20 },
                { 4, 20 },
                { 5, 20 }
            });
            break;
        }
    }
}

Tetromino::Tetromino(Tetromino &original)
{
    shape = original.shape;
    position = original.position;
    color = original.color;
    rotationState = original.rotationState;
}


/// @return true if move successful, false if unsuccessful
bool Tetromino::move(int x, int y, SquareContent playingField[10][24])
{
    // check for position validity
    for (int i = 0; i < 4; i++)
    {
        if (position.get(i, 0) + x < 0 || position.get(i, 0) + x > 9 || position.get(i, 1) + y < 0 ||
            playingField[position.get(i, 0)+x][position.get(i,1)+y] != SquareContent::Empty)
        {
            return false;
        }
    }

    // since the position is valid, move
    for (int i = 0; i < 4; i++)
    {
        position.set(i, 0, position.get(i, 0) + x);
        position.set(i, 1, position.get(i, 1) + y);
    }

    return true;
}

MoveDownResult Tetromino::moveDown(SquareContent playingField[10][24], int lockDelay, int lockDelayTimer)
{
    // check for position validity
    for (int i = 0; i < 4; i++)
    {
        if (position.get(i,1)-1 < 0 || playingField[position.get(i,0)][position.get(i,1)-1] != SquareContent::Empty)
        {
            // if not, set down tetromino, unless lockdelay is still active
            if (lockDelayTimer > lockDelay)
            {
                for (int j = 0; j < 4; j++)
                {
                    playingField[position.get(j,0)][position.get(j,1)] = (SquareContent) this->shape;
                }

                // now check if it was set down above the screen
                for (int j = 0; j < 4; j++)
                {
                    if (position.get(j,1) > 19)
                    {
                        return MoveDownResult::PlacedDownAboveScreen;
                    }
                }

                return MoveDownResult::PlacedDown;
            }

            // else
            return MoveDownResult::LockDelayActive;
        }
    }

    // if yes, move down
    move(0, 1, playingField);
    return MoveDownResult::MovedDown;
}

void Tetromino::rotate(bool clockwise, SquareContent playingField[10][24])
{
    Tetromino rotated(*this);

    int kickValues[5][2];

    switch (rotated.shape)
    {
        // O piece does nothing
        case Shape::O:
            return;

        // I piece is special because no rotation coordinates
        case Shape::I:
        {
            int kickValuesTable[4][5][2] = 
            {
                { {0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2} },
                { {0, 0}, {-1, 0}, {2, 0}, {1, -2}, {2, -1} },
                { {0, 0}, {2, 0}, {-1, 0}, {2, 1}, {-1, -2} },
                { {0, 0}, {1, 0}, {-2, 0}, {1, -2}, {-2, 1} }
            };
            for (int i = 0; i < 5; i++)
            {
                kickValues[i][0] = kickValuesTable[(rotated.rotationState + (!clockwise)) % 4][i][0];
                kickValues[i][1] = kickValuesTable[(rotated.rotationState + (!clockwise)) % 4][i][1];
            }

            // project the moving piece to a 4x4 matrix for calculation purposes and swap x with y
            Position unitPos;
            Position unitPosCopy;
            for (int i = 0; i < 4; i++)
            {
                unitPosCopy.set(i, 1 - rotated.rotationState % 2, 1 + (rotated.rotationState < 2));
                unitPosCopy.set(i, rotated.rotationState % 2, rotated.position.get(i,rotated.rotationState%2) - rotated.position.get(3,rotated.rotationState%2));

                unitPos.set(i, rotated.rotationState % 2, 1 + (rotated.rotationState < 2));
                unitPos.set(i, 1 - rotated.rotationState % 2, rotated.position.get(i,rotated.rotationState%2) - rotated.position.get(3,rotated.rotationState%2));
            }

            if (clockwise)
            {
                rotated.rotationState = (rotated.rotationState + 1) % 4;

                if (rotated.rotationState % 2 == 0)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        unitPos.set(i, 1, unitPos.get(i,1) + 1 - rotated.rotationState);
                    }
                }
            }

            else
            {
                if (rotated.rotationState % 2 == 0)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        unitPos.set(i, 0, unitPos.get(i, 0) + 1 - rotated.rotationState);
                    }
                }

                for (int i = 0; i < 5; i++)
                {
                    kickValues[i][0] *= -1;
                    kickValues[i][1] *= -1;
                }

                rotated.rotationState = (rotated.rotationState + 3) % 4;
            }

            for (int i = 0; i < 4; i++)
            {
                rotated.position.set(i, 0, rotated.position.get(i,0) + unitPos.get(i,0) - unitPosCopy.get(i,0));
                rotated.position.set(i, 1, rotated.position.get(i,1) + unitPos.get(i,1) - unitPosCopy.get(i,1));
            }

            break;
        }

        // all other pieces
        // the third block is the center of rotation for these
        default:
        {
            int kickValuesTable[4][5][2] =
            {
                { {0, 0}, {-1, 0}, {-1, 1},  {0, -2}, {-1, -2} },
                { {0, 0}, {1, 0},  {1, -1},  {0, 2},  {1, 2}   },
                { {0, 0}, {1, 0},  {1, 1},   {0, -1}, {1, -2}  },
                { {0, 0}, {-1, 0}, {-1, -1}, {0, 2},  {-1, 2}  }
            };
            for (int i = 0; i < 5; i++)
            {
                kickValues[i][0] = kickValuesTable[(rotated.rotationState + !clockwise) % 4][i][0];
                kickValues[i][1] = kickValuesTable[(rotated.rotationState + !clockwise) % 4][i][1];
            }

            Position unitPos;
            Position unitPosCopy;
            for (int i = 0; i < 4; i++)
            {
                unitPosCopy.set(i, 0, rotated.position.get(i, 0) - rotated.position.get(2, 0));
                unitPosCopy.set(i, 1, rotated.position.get(i, 1) - rotated.position.get(2, 1));

                unitPos.set(i, 0, rotated.position.get(i, 0) - rotated.position.get(2, 0));
                unitPos.set(i, 1, rotated.position.get(i, 1) - rotated.position.get(2, 1));
            }

            if (clockwise)
            {
                for (int i = 0; i < 4; i++)
                {
                    auto tmp = unitPos.get(i, 0);
                    unitPos.set(i, 0, unitPos.get(i, 1));
                    unitPos.set(i, 1, -tmp);
                }

                rotated.rotationState = (rotated.rotationState + 1) % 4;
            }

            else
            {
                for (int i = 0; i < 4; i++)
                {
                    auto tmp = unitPos.get(i, 0);
                    unitPos.set(i, 0, -unitPos.get(i, 1));
                    unitPos.set(i, 1, tmp);
                }

                rotated.rotationState = (rotated.rotationState + 3) % 4;
            }

            for (int i = 0; i < 4; i++)
            {
                rotated.position.set(i, 0, rotated.position.get(i,0) + unitPos.get(i,0) - unitPosCopy.get(i,0));
                rotated.position.set(i, 1, rotated.position.get(i,1) + unitPos.get(i,1) - unitPosCopy.get(i,1));
            }

            break;
        }
    }

    for (int i = 0; i < 5; i++)
    {
        if (rotated.move(kickValues[i][0], kickValues[i][1], playingField))
            break;
        
        if (i == 4)
            return;
    }

    position = rotated.position;
    rotationState = rotated.rotationState;
}

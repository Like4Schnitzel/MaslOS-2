#include "Tetromino.hpp"

Tetromino::Tetromino(Shape shape)
{
    rotationState = 0;
    color = ShapeToRGB(shape);

    switch (shape)
    {
        case Shape::O: {
            position = Position((int[4][2]) {
                { 4, 21 },
                { 5, 21 },
                { 4, 20 },
                { 5, 20 }
            });
            break;
        }

        case Shape::I: {
            position = Position((int[4][2]) {
                { 6, 20 },
                { 5, 20 },
                { 4, 20 },
                { 3, 20 }
            });
            break;
        }

        case Shape::J: {
            position = Position((int[4][2]) {
                { 3, 21 },
                { 3, 20 },
                { 4, 20 },
                { 5, 20 }
            });
            break;
        }

        case Shape::L: {
            position = Position((int[4][2]) {
                { 5, 21 },
                { 3, 20 },
                { 4, 20 },
                { 5, 20 }
            });
            break;
        }

        case Shape::S: {
            position = Position((int[4][2]) {
                { 4, 21 },
                { 5, 21 },
                { 4, 20 },
                { 3, 20 }
            });
            break;
        }

        case Shape::Z: {
            position = Position((int[4][2]) {
                { 3, 21 },
                { 4, 21 },
                { 4, 20 },
                { 5, 20 }
            });
            break;
        }

        case Shape::T: {
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

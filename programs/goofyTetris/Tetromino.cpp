#include "Tetromino.hpp"

Tetromino::Tetromino(Shape shape)
{
    rotationState = 0;

    switch (shape)
    {
        case Shape::O: {
            color = (unsigned char[3]) {240, 240, 0};
            position = Position((int[4][2]) {
                { 4, 21 },
                { 5, 21 },
                { 4, 20 },
                { 5, 20 }
            });
            break;
        }

        case Shape::I: {
            color = (unsigned char[3]) {0, 240, 240};
            position = Position((int[4][2]) {
                { 6, 20 },
                { 5, 20 },
                { 4, 20 },
                { 3, 20 }
            });
            break;
        }

        case Shape::J: {
            color = (unsigned char[3]) {0, 0, 240};
            position = Position((int[4][2]) {
                { 3, 21 },
                { 3, 20 },
                { 4, 20 },
                { 5, 20 }
            });
            break;
        }

        case Shape::L: {
            color = (unsigned char[3]) {240, 160, 0};
            position = Position((int[4][2]) {
                { 5, 21 },
                { 3, 20 },
                { 4, 20 },
                { 5, 20 }
            });
            break;
        }

        case Shape::S: {
            color = (unsigned char[3]) {0, 240, 0};
            position = Position((int[4][2]) {
                { 4, 21 },
                { 5, 21 },
                { 4, 20 },
                { 3, 20 }
            });
            break;
        }

        case Shape::Z: {
            color = (unsigned char[3]) {240, 0, 0};
            position = Position((int[4][2]) {
                { 3, 21 },
                { 4, 21 },
                { 4, 20 },
                { 5, 20 }
            });
            break;
        }

        case Shape::T: {
            color = (unsigned char[3]) {160, 0, 240};
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

#pragma once
#include "Position.cpp"
#include "RGB.hpp"
#include "enums.hpp"

RGB ShapeToRGB(Shape shape)
{
    switch (shape)
    {
        case Shape::O: return (unsigned char[3]) {240, 240, 0};
        case Shape::I: return (unsigned char[3]) {0, 240, 240};
        case Shape::J: return (unsigned char[3]) {0, 0, 240};
        case Shape::L: return (unsigned char[3]) {240, 160, 0};
        case Shape::S: return (unsigned char[3]) {0, 240, 0};
        case Shape::Z: return (unsigned char[3]) {240, 0, 0};
        case Shape::T: return (unsigned char[3]) {160, 0, 240};
    }
}

class Tetromino {
    private:
        Position position;
        Shape shape;
        RGB color;
        int rotationState;
    public:
        Tetromino(Shape shape);
        Tetromino(Tetromino &original);
        bool move(int x, int y, SquareContent playingField[240]);
};

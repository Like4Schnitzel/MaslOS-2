#pragma once
#include "Position.cpp"
#include "RGB.hpp"

enum class Shape {I, O, T, S, Z, J, L};

class Tetromino {
    private:
        Position position;
        Shape shape;
        RGB color;
        int rotationState;
    public:
        Tetromino(Shape shape);
        Tetromino(Tetromino &original);
};

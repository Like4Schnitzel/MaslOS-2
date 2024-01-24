#include "RGB.hpp"

RGB::RGB() {}

RGB::RGB(unsigned char colors[3])
{
    for (int i = 0; i < 3; i++)
    {
        vals[i] = colors[i];
    }
}

unsigned char RGB::get(int index)
{
    return vals[index];
}

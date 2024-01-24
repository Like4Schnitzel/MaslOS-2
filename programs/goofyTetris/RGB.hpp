#pragma once

class RGB {
    private:
        unsigned char vals[3];
    public:
        RGB();
        RGB(unsigned char colors[3]);

        unsigned char get(int index);
};

#ifndef COLOR_H
#define COLOR_H

#include "src/number.h"

class Color
{
public:
    Color();
    Color(uint8 r, uint8 g, uint8 b);
    Color(const Color &color);
    Color(uint8 gray);

    uint8 getRed() const;
    void setRed(uint8 value);

    uint8 getGreen() const;
    void setGreen(uint8 value);

    uint8 getBlue() const;
    void setBlue(uint8 value);

    void setGray(uint8 gray);

    Color operator*(float factor) const;
    Color &operator+=(const Color &other);

private:
    uint8 r, g, b;
};

#endif // COLOR_H

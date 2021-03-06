#include "line.h"

#include <cmath>

Line::Line()
{
}

Line::Line(const Vec2 &p1, const Vec2 &p2) :
    p1(p1),
    p2(p2)
{
}

Vec2 Line::getP1() const
{
    return p1;
}

void Line::setP1(const Vec2 &value)
{
    p1 = value;
}

Vec2 Line::getP2() const
{
    return p2;
}

void Line::setP2(const Vec2 &value)
{
    p2 = value;
}

float Line::length()
{
    int32 dx = p1.getX() - p2.getX();
    int32 dy = p1.getY() - p2.getY();
    return sqrt(dx * dx + dy * dy);
}

#include "Position2D.h"


Position2D::Position2D()
{
}
Position2D::Position2D(float x, float y) :_x(x), _y(y)
{
}


Position2D::~Position2D()
{
}

float Position2D::getX() { return _x; }
float Position2D::getY() { return _y; }


void Position2D::setX(float x) { _x = x; }
void Position2D::setY(float y) { _y = y; }
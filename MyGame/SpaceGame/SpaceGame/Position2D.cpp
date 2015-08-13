#include "Position2D.h"


Position2D::Position2D()
{
}
Position2D::Position2D(int x, int y) :_x(x), _y(y)
{
}


Position2D::~Position2D()
{
}

int Position2D::getX() { return _x; }
int Position2D::getY() { return _y; }


void Position2D::setX(int x) { _x = x; }
void Position2D::setY(int y) { _y = y; }
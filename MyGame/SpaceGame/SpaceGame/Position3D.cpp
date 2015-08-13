#include "Position3D.h"

Position3D::Position3D() : Position2D(0, 0), _z(0){}

Position3D::Position3D(int x, int y, int z) : Position2D(x, y), _z(z)
{
}


Position3D::~Position3D()
{
}


int Position3D::getZ() { return _z; }

void Position3D::setZ(int z) { _z = z; }
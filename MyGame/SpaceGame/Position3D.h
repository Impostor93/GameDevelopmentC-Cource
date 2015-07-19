#pragma once
#include "Position2D.h"

class Position3D : public Position2D
{
public:
	Position3D();
	Position3D(int x, int y,int z);
	~Position3D();

	int getZ();
	void setZ(int z);

private:
	int _z;
};


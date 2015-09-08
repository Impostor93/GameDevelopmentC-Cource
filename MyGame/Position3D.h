#pragma once
#include "Position2D.h"

class Position3D : public Position2D
{
public:
	Position3D();
	Position3D(float x, float y, float z);
	~Position3D();

	float getZ();

private:
	float _z;

protected:
	void setZ(float z);
};


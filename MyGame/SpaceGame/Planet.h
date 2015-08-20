#pragma once
#ifndef PLANET
#define PLANET

#include "StaticGameEntity.h"

class Planet : public StaticGameEntity
{
public:
	Planet(CIndieLib* masterInstance, Position3D position, const char* path, IND_Surface* surface, SpriteCordinateMapper* spriteMapper, float* deltaTime);
	~Planet();
};

#endif // !PLANET
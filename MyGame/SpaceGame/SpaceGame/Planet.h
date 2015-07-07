#pragma once
#ifndef PLANET
#define PLANET

#include "GameEntity.h"

class Planet : public GameEntity
{
public:
	Planet(CIndieLib* masterInstance, Position3D position, const char* path);
	~Planet();
};

#endif // !PLANET
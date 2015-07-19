#pragma once
#ifndef PLANET
#define PLANET

#include "StaticGameEntity.h"

class Planet : public StaticGameEntity
{
public:
	Planet(CIndieLib* masterInstance, Position3D position, const char* path);
	~Planet();
};

#endif // !PLANET
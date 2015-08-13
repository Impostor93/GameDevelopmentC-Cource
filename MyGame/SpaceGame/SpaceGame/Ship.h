#pragma once
#ifndef SHIP
#define SHIP

#include "StaticGameEntity.h"

class Ship : public StaticGameEntity
{
public:
	Ship(CIndieLib* masterInstance, Position3D position, const char* path);
	~Ship();
};

#endif
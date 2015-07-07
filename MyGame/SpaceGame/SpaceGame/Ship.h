#pragma once
#ifndef SHIP
#define SHIP

#include "GameEntity.h"

class Ship: public GameEntity
{
public:
	Ship(CIndieLib* masterInstance, Position3D position, const char* path);
	~Ship();
};

#endif
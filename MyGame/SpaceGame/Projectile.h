#pragma once
#ifndef PROJECTILE
#define PROJECTILE

#include "StaticGameEntity.h"

class Projectile : public StaticGameEntity
{
public:
	Projectile(CIndieLib* masterInstance, Position3D position, const char* path);
	~Projectile();
};

#endif
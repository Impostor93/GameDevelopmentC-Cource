#pragma once
#ifndef BACKGROUND
#define BACKGROUND

#include "CIndieLib.h"
#include "StaticGameEntity.h"
#include "SpriteCordinateMapper.h"

class Space : public StaticGameEntity
{
public:
	Space(CIndieLib* masterInstance, Position3D position, const char* path, IND_Surface* surface, SpriteCordinateMapper* spriteMapper, float* deltaTime);
	~Space();
};

#endif
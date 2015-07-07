#pragma once
#ifndef BACKGROUND
#define BACKGROUND

#include "CIndieLib.h"
#include "GameEntity.h"

class Space : public GameEntity
{
public:
	Space(CIndieLib* masterInstance, Position3D position, const char* path);
	~Space();
};

#endif
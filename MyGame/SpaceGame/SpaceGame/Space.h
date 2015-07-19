#pragma once
#ifndef BACKGROUND
#define BACKGROUND

#include "CIndieLib.h"
#include "StaticGameEntity.h"

class Space : public StaticGameEntity
{
public:
	Space(CIndieLib* masterInstance, Position3D position, const char* path);
	~Space();
};

#endif
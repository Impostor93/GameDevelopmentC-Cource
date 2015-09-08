#pragma once
#ifndef STATICGAMEENTITY_H
#define STATICGAMEENTITY_H

#include "CIndieLib.h"
#include "Position3D.h"
#include "IND_Entity2d.h"
#include "IND_SurfaceManager.h"
#include "IND_Surface.h"
#include "Region.h"
#include "GameEntity.h"
#include "SpriteCordinateMapper.h"

class StaticGameEntity: public GameEntity
{
private:
	SpriteCordinateMapper* _spriteMapper;

public:
	StaticGameEntity(CIndieLib* masterInstance, Position3D position, std::string resource, IND_Surface* surface, SpriteCordinateMapper* spriteMapper, float* deltaTime);
	~StaticGameEntity();

	void destroy();
	void draw();

	void update();

	void changeResource(std::string resource);

};
#endif

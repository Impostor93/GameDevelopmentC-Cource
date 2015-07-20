#pragma once
#ifndef StaticGameEntity_H
#define StaticGameEntity_H

#include "CIndieLib.h"
#include "Position3D.h"
#include "IND_Entity2d.h"
#include "IND_SurfaceManager.h"
#include "IND_Surface.h"
#include "Region.h"
#include "GameEntity.h"

class StaticGameEntity: public GameEntity
{
private:
	IND_Surface* _surface;
protected:
	IND_Surface* getSurface();

public:
	StaticGameEntity(CIndieLib* masterInstance, Position3D position, const char* resourcePath);
	~StaticGameEntity();

	void Destroy();
	void Draw();
	void Rotate();
};
#endif

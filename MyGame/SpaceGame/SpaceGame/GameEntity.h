#pragma once
#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include "CIndieLib.h"
#include "Position3D.h"
#include "IND_Entity2d.h"
#include "IND_SurfaceManager.h"
#include "IND_Surface.h"
#include "Region.h"

class GameEntity
{
private:
	CIndieLib* _masterInstance = 0;
	Position3D _position;
	const char* _resourcePath;

	IND_Surface* _surface;
	IND_Entity2d* _entity;

public:
	GameEntity(CIndieLib* master, Position3D position,const char* resourcePath);
	~GameEntity();

	virtual void Draw();

	virtual void DrawRegion(Region* region);

	virtual void Destroy();

	Position3D getPosition();

	void setPosition(Position3D position);

protected:
	IND_Entity2d* getEntity();
	IND_Surface* getSurface();
};
#endif
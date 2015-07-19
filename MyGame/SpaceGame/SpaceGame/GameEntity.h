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
	IND_Entity2d* _entity;
	Position3D _position;
	const char* _resourcePath;

public:
	GameEntity(CIndieLib* master, Position3D position,const char* resourcePath);
	~GameEntity();

	virtual void Draw()=0;

	virtual void DrawRegion(Region* region);

	virtual void Destroy()=0;

	Position3D getPosition();
	void setPosition(Position3D position);

	IND_Entity2d* getINDIEntity();

protected:
	CIndieLib* getMasterInstance();
	const char*  getResourcePath();
};
#endif
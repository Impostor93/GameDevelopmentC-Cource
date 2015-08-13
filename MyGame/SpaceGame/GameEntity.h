#pragma once
#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include "CIndieLib.h"
#include "Position3D.h"
#include "IND_Entity2d.h"
#include "IND_SurfaceManager.h"
#include "IND_Surface.h"
#include "Region.h"
#include <sstream>
#include "Common.h"

class GameEntity
{
private:
	CIndieLib* _masterInstance = 0;
	IND_Entity2d* _entity;

	const char* _resourcePath;
	std::string _tempResourcePath;

	const std::string _positionKey = "Position";
	const std::string _angleZKey = "angleZ";
	const std::string _resourcePathKey = "ResourcePath";

	float _width;
	float _height;

public:
	GameEntity(CIndieLib* master, Position3D position, const char* resourcePath, float* deltaTime);

	~GameEntity();

	virtual void draw()=0;
	virtual void drawRegion(Region* region);
	virtual void destroy()=0;

	Position3D getPosition();
	void setPosition(Position3D position);

	IND_Entity2d* getINDIEntity();
	IND_Entity2d* getColisionBorder();

	std::string serializeEntityState();
	void deserializeEntity(std::string jsonEntity);

	virtual void moveForward(float acceleration, bool lockInWindow);

	virtual void moveBackward(float acceleration);

	void rotateLeft(float rotationSpeed);
	void rotateRight(float rotationSpeed);

protected:
	Position3D _position;
	float* _deltaTime;

	float _angleZ = 0;

	CIndieLib* getMasterInstance();
	const char*  getResourcePath();
};
#endif
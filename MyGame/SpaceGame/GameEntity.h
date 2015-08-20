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
	IND_Surface* _surface;

	std::string _resourcePath;
	std::string _tempResourcePath;

	const std::string _positionKey = "Position";
	const std::string _angleZKey = "angleZ";
	const std::string _resourcePathKey = "ResourcePath";

	float _width;
	float _height;

public:
	GameEntity(CIndieLib* master, Position3D position, std::string resourcePath, IND_Surface* surface, float* deltaTime);

	~GameEntity();

	virtual void draw()=0;
	virtual void destroy()=0;
	virtual void update();

	void setPosition(Position3D position);

	Position3D getPosition();
	IND_Entity2d* getINDIEntity();
	IND_Surface* getSurface();

	std::string serializeEntityState();
	void deserializeEntity(std::string jsonEntity);

	virtual void moveForward(float acceleration, bool lockInWindow);
	virtual void moveBackward(float acceleration);

	void rotateLeft(float rotationSpeed);
	void rotateRight(float rotationSpeed);

	std::string  getResourcePath();

protected:
	Position3D _position;
	float* _deltaTime;

	float _angleZ = 0;

	CIndieLib* getMasterInstance();
};
#endif
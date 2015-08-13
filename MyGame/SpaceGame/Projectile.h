#pragma once
#ifndef PROJECTILE
#define PROJECTILE

#include "StaticGameEntity.h"

class Projectile : public StaticGameEntity
{
private:
	float _speedX = 0;
	float _speedY = 0;

public:
	Projectile(CIndieLib* masterInstance, Position3D position, const char* path, float* deltaTime);
	~Projectile();

	void moveForward(float acc, bool lockInWindowScreen);

	void setSpeed(float angle);
};

#endif
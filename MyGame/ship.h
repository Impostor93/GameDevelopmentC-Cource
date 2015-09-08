#pragma once
#ifndef SHIP_H
#define SHIP_H

#include "StaticGameEntity.h"
#include "AnimatedGameEntity.h"
#include "Projectile.h"

#define maxProjectiels 10u

class Ship : public AnimatedGameEntity
{
private:
	Projectile* _projectile[maxProjectiels];
	int projectileIndex = -1;
	int _balnsior = 0;
	double projectileSpeed = 1000.0;
	
	int _health = 100;
	int _shoots = 0;

public:
	Ship(CIndieLib* masterInstance, Position3D position, std::string path, IND_Surface* surface, AnimationMapper* animationMapper, float* deltaTime);
	~Ship();

	void FireShoot();

	void moveForward(float acceleration, bool lockInWindow);

	void update();

	Projectile** getProjectiles();
	
	int getHealth();
	void doDamage(GameEntity* contactEntity);
};

#endif
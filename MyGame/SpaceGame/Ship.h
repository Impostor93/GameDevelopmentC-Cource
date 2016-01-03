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
	int _reloadTimeInSeconds = 10;

	ShipState _shipState;
	ShipRotationState _shipRotateState;

	float _angle;

	IND_Timer* _reloeadBulletTimer;

public:
	Ship(CIndieLib* masterInstance, Position3D position, std::string path, IND_Surface* surface, AnimationMapper* animationMapper, float* deltaTime);
	~Ship();

	void FireShoot();

	void moveForward(float acceleration, bool lockInWindow);
	void moveBackward(float acceleration, bool lockInWindow);

	void update();

	Projectile** getProjectiles();
	
	int getHealth();
	int getShootCount();
	void doDamage(GameEntity* contactEntity);

	void changeState(ShipState shipState);
	void changeShipRotationState(ShipRotationState newState);

	ShipState getState();
	ShipRotationState getShipRotateState();

	std::string getShootTimerTicks();

protected:
	Position2D calcuateNewPositionOnMovingForward();
	Position2D calcuateNewPositionOnMovingBackward();
};

#endif
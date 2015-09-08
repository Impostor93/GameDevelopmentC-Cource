#pragma once

#ifndef GAMEENGINE
#define GAMEENGINE

#include "CIndieLib.h"
#include "IND_Surface.h"
#include "IND_Entity2d.h"
#include "GameEntity.h"
#include "ship.h"
#include "Space.h"
#include "SpaceBody.h"
#include "IND_Animation.h"
#include "IND_AnimationManager.h"
#include "AnimatedGameEntity.h"
#include "GameEntityManager.h"
#include "SpriteCordinateMapper.h"
#include "AnimationMapper.h"
#include "HUD.h"

class GameEngine
{
private:
	CIndieLib *_masterInstance;
	GameEntityManager* _entityManager;
	SpriteCordinateMapper* _spriteCordinates;
	AnimationMapper* _animationMapper;

	const float _maxAccelerationValue = 600.f;
	const float _accelerationStep = 1.f;

	float rotation = 0;
	float* mDelta = new float(0);

	float mAngle = 0;
	float acc = 0.0f;

	int rotateSpeed = 200;

public:
	GameEngine(CIndieLib* _masterInstance);

	void initialize();
	void processUserInput();
	void update();
	void manageCollisions();

	~GameEngine();
};

#endif
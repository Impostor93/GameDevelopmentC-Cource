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
#include "irrKlang.h"
#include "AudioPlayer.h"
#include "Font.h"
#include "FontManager.h"

class GameEngine
{
private:
	CIndieLib *_masterInstance;
	GameEntityManager* _entityManager;
	FontManager* _fontManager;

	SpriteCordinateMapper* _spriteCordinates;
	AnimationMapper* _animationMapper;
	irrklang::ISoundEngine* _soundEngine;

	const float _accelerationStep = 1.f;

	float rotation = 0;
	float* mDelta = new float(0);

	float mAngle = 0;

	bool _stopRotating = false;

	int rotateSpeed = 200;

	void _onShipCollition(Ship* ship);

	std::string _projectRoot = "D:/Projects/.Net Projects/SpaceGame/GameDevelopmentC-Cource/MyGame";
public:
	GameEngine(CIndieLib* _masterInstance);

	void initializeEntities();
	void initializeFonts();
	void processUserInput();
	void update();
	void manageCollisions();
	void clearScene();

	~GameEngine();
};

#endif
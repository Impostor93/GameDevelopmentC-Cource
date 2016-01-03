#include "GameEngine.h"


GameEngine::GameEngine(CIndieLib* _masterInstance)
	:_masterInstance(_masterInstance)
{
	_spriteCordinates = new SpriteCordinateMapper();
	_animationMapper = new AnimationMapper(_spriteCordinates);
	_soundEngine = irrklang::createIrrKlangDevice();

	_entityManager = new GameEntityManager(_masterInstance, _spriteCordinates, _animationMapper, (_projectRoot + "/SpriteAndAnimation/Sprite.png").c_str(), _soundEngine, mDelta);
	_fontManager = new FontManager(_masterInstance, mDelta);

	//_soundEngine->play2D("D:/Vs2012 Project/C++ game development course/ShipGame/GameDevelopmentC-Cource/MyGame/SpaceGame/irrKlang/OriginalIrrKlang/media/Devil_May_Cry_3-_Taste_the_Blood_with_lyrics_and_d.ogg");
}
void GameEngine::initializeFonts()
{
	_fontManager->addIndiFont("smallFont", _projectRoot + "/SpaceGame/resources/font_small.png", _projectRoot + "/SpaceGame/resources/font_small.xml");

	_fontManager->draw();
}
void GameEngine::initializeEntities()
{
	_spriteCordinates->loadSpriteMap(_projectRoot + "/SpriteAndAnimation/Sprite.txt");
	_animationMapper->loadAnimationeMap(_projectRoot + "/SpriteAndAnimation/Animations.txt");

	*mDelta = _masterInstance->_render->getFrameTime() / 1000.0f;

	_entityManager->createAndAddEntity("Ship", ShipObject, Position3D(600, 600, 3), "Ship");
	_entityManager->createAndAddEntity("Space", StaticObject, Position3D(0, 0, 1), "background");

	_entityManager->createAndAddEntity("Asteroid", SpaceBodyObject, Position3D(300, 150, 4), "asteroid");
	_entityManager->createAndAddEntity("SmallPlanet", SpaceBodyObject, Position3D(580, 315, 4), "planet1");
	_entityManager->createAndAddEntity("MediumPlanet", SpaceBodyObject, Position3D(3, 170, 4), "planet2");
	_entityManager->createAndAddEntity("RedPlanet", SpaceBodyObject, Position3D(360, 300, 4), "planet3");
	_entityManager->createAndAddEntity("BluePlanet", SpaceBodyObject, Position3D(890, 180, 4), "planet4");

	_entityManager->createAndAddEntity("ass1", SpaceBodyObject, Position3D(390, 150, 4), "ass1");
	_entityManager->createAndAddEntity("ass1.1", SpaceBodyObject, Position3D(250, 350, 4), "ass1");
	_entityManager->createAndAddEntity("ass1.2", SpaceBodyObject, Position3D(230, 380, 4), "ass1");
	_entityManager->createAndAddEntity("ass1.3", SpaceBodyObject, Position3D(190, 150, 4), "ass1");
	_entityManager->createAndAddEntity("ass1.5", SpaceBodyObject, Position3D(650, 150, 4), "ass1");
	_entityManager->createAndAddEntity("ass1.6", SpaceBodyObject, Position3D(1000, 390, 4), "ass1");
	_entityManager->createAndAddEntity("ass2", SpaceBodyObject, Position3D(890, 350, 4), "ass2");
	_entityManager->createAndAddEntity("ass2.2", SpaceBodyObject, Position3D(630, 150, 4), "ass2");
	_entityManager->createAndAddEntity("ass3", SpaceBodyObject, Position3D(200, 330, 4), "ass3");
	_entityManager->createAndAddEntity("ass3.1", SpaceBodyObject, Position3D(530, 280, 4), "ass3");
	_entityManager->createAndAddEntity("ass3.2", SpaceBodyObject, Position3D(730, 250, 4), "ass3");

	Ship* ship = (Ship*)_entityManager->getEntity("Ship");
	_entityManager->createAndAddEntity("HUD", HUDObject, Position3D(0, 0, 10), "orb + orb holder NEW");
	HUD* hud = ((HUD*)_entityManager->getEntity("HUD"));
	hud->setEntityToFollow(ship);

	_entityManager->drawEntities();

	ship->setHotSpot(0.5f, 0.5f);

	ship->getINDIEntity()->setBoundingRectangle("Ship-Body-Right", 50, 35, 10, 60);
	ship->getINDIEntity()->setBoundingRectangle("Ship-Body-Left", 15, 35, 10, 60);
	ship->getINDIEntity()->setBoundingRectangle("Ship-Bottom", 16, 95, 44, 1);
	ship->getINDIEntity()->setBoundingTriangle("Ship-Top", 18, 35, 38, 10, 57, 35);

	_entityManager->setCircleCollisionArea("Asteroid", 72, 78, 60);
	_entityManager->setCircleCollisionArea("SmallPlanet", 100, 100, 73);
	_entityManager->setCircleCollisionArea("RedPlanet", 50, 50, 50);
	_entityManager->setCircleCollisionArea("MediumPlanet", 100, 101, 95);
	_entityManager->setCircleCollisionArea("BluePlanet", 110, 110, 96);
	_entityManager->setCircleCollisionArea("ass1", 15, 15, 12);
	_entityManager->setCircleCollisionArea("ass1.1", 15, 15, 12);
	_entityManager->setCircleCollisionArea("ass1.2", 15, 15, 12);
	_entityManager->setCircleCollisionArea("ass1.3", 15, 15, 12);
	_entityManager->setCircleCollisionArea("ass1.5", 15, 15, 12);
	_entityManager->setCircleCollisionArea("ass1.6", 15, 15, 12);
	_entityManager->setCircleCollisionArea("ass2", 63, 96, 44);
	_entityManager->setCircleCollisionArea("ass2.2", 63, 96, 44);
	_entityManager->setCircleCollisionArea("ass3", 27, 26, 20);
	_entityManager->setCircleCollisionArea("ass3.1", 27, 26, 20);
	_entityManager->setCircleCollisionArea("ass3.2", 27, 26, 20);
}

void GameEngine::update()
{
	*mDelta = _masterInstance->_render->getFrameTime() / 1000.0f;

	_fontManager->update();
	_entityManager->update();

	Ship* ship = ((Ship*)_entityManager->getEntity("Ship"));

	if (ship->getState() == Accelerate)
	{
		if (ship->isAnimationStoped())
			ship->startAnimation();

		ship->moveForward(_accelerationStep, true);
	}
	else if (ship->getState() == Soar)
	{
		ship->moveForward(-_accelerationStep * 2, true);

		if (!ship->isAnimationStoped())
			ship->stopAnimation();
	} 
	else if (ship->getState() == ReflectBack)
	{
		ship->moveBackward(_accelerationStep * 2, true);
	} 
	else if (ship->getState() == ReflectFront)
	{
		ship->moveForward(-_accelerationStep * 2, true);
	}

	if (ship->getShipRotateState() == ShipRotationState::Right)
	{
		ship->rotateRight(rotateSpeed);
		ship->changeShipRotationState(ShipRotationState::None);
	}
	else if (ship->getShipRotateState() == ShipRotationState::Left)
	{
		ship->rotateLeft(rotateSpeed);
		ship->changeShipRotationState(ShipRotationState::None);
	}

	if (ship->getAcceleration() <= 0)
		ship->changeState(Peace);
}

void GameEngine::processUserInput()
{
	Ship* ship = (Ship*)_entityManager->getEntity("Ship");

	if ((_masterInstance->_input->isKeyPressed(IND_ESCAPE)))
	{
		_masterInstance->_render->endScene();
		_masterInstance->end();
		exit(0);
	}

	if (_masterInstance->_input->onKeyPress(IND_SPACE))
		ship->FireShoot();

	if ((_masterInstance->_input->isKeyPressed(IND_KEYLEFT))) //left
	{
		ship->changeShipRotationState(ShipRotationState::Left);	
	}
	if ((_masterInstance->_input->isKeyPressed(IND_KEYRIGHT))) //right
	{
		ship->changeShipRotationState(ShipRotationState::Right);
	}

	if ((_masterInstance->_input->isKeyPressed(IND_KEYUP))) //flying
	{
		if (ship->getState() != ReflectBack && ship->getState() != ReflectFront)
			ship->changeState(Accelerate);
	}
	else
	{
		if (ship->getState() != ReflectBack && ship->getState() != ReflectFront)
			ship->changeState(Soar);
	}

	if ((_masterInstance->_input->isKeyPressed(IND_KEYDOWN))) //flyingbackwards
		ship->changeState(Soar);

	if (_masterInstance->_input->isKeyPressed(IND_F12))
	{
		_entityManager->saveEntities("../save.js");
	}
	if (_masterInstance->_input->isKeyPressed(IND_F11))
	{
		_entityManager->loadEntityFromJSON("../save.js", mDelta);
	}
}

void GameEngine::manageCollisions()
{
	Ship* ship = ((Ship*)_entityManager->getEntity("Ship"));

	map<std::string, GameEntity*> gameEntityes = _entityManager->getEntities();
	for (std::map<std::string, GameEntity*>::iterator it = gameEntityes.begin(); it != gameEntityes.end(); ++it)
	{
		Projectile** projectiles = ship->getProjectiles();
		int br = 0;
		
		if (_entityManager->getType(it->first) == SpaceBodyObject)
		{
			while (br < maxProjectiels)
			{
				if (_entityManager->checkForCollision("Projectile", (*projectiles), it->first, it->second))
				{
					((SpaceBody*)it->second)->doDamage();
					(*projectiles)->destroy();
				}

				*projectiles++;
				br++;
			}

			//TODO: calculate damage based on acceleration 
			if (_entityManager->checkForCollision("Ship-Top", ship, it->first, it->second))
			{
				ship->moveBackward(_accelerationStep, true);
				ship->changeState(ReflectBack);
				ship->doDamage(it->second);

				if (ship->getShipRotateState() == ShipRotationState::Left)
					ship->changeShipRotationState(ShipRotationState::Right);
				else if (ship->getShipRotateState() == ShipRotationState::Right)
					ship->changeShipRotationState(ShipRotationState::Left);
			}
			if (_entityManager->checkForCollision("Ship-Bottom", ship, it->first, it->second))
			{
				ship->moveForward(_accelerationStep, true);
				ship->changeState(ReflectFront);
				ship->doDamage(it->second);

				if (ship->getShipRotateState() == ShipRotationState::Left)
					ship->changeShipRotationState(ShipRotationState::Right);
				else if (ship->getShipRotateState() == ShipRotationState::Right)
					ship->changeShipRotationState(ShipRotationState::Left);
			}
			if (_entityManager->checkForCollision("Ship-Body-Left", ship, it->first, it->second))
			{
				if (ship->getState() == Soar)
				{
					ship->changeState(ReflectBack);
				}
				else
				{
					_stopRotating = true;
					ship->rotateRight(rotateSpeed);
				}
				if (ship->getShipRotateState() == ShipRotationState::Left)
					ship->changeShipRotationState(ShipRotationState::Right);
				else if (ship->getShipRotateState() == ShipRotationState::Right)
					ship->changeShipRotationState(ShipRotationState::Left);
			}
			if (_entityManager->checkForCollision("Ship-Body-Right", ship, it->first, it->second))
			{
				if (ship->getState() == Soar)
				{
					ship->changeState(ReflectBack);
				}
				else
				{
					_stopRotating = true;
					ship->rotateLeft(rotateSpeed);
				}

				if (ship->getShipRotateState() == ShipRotationState::Left)
					ship->changeShipRotationState(ShipRotationState::Right);
				else if (ship->getShipRotateState() == ShipRotationState::Right)
					ship->changeShipRotationState(ShipRotationState::Left);
			}
		}
	}
}
void GameEngine::_onShipCollition(Ship* ship)
{
	if (ship->getState() == ReflectBack)
	{
		ship->moveForward(_accelerationStep, true);
		ship->changeState(ReflectFront);
	}
	else
	{
		ship->moveBackward(_accelerationStep, true);
		ship->changeState(ReflectBack);
	}
}

void GameEngine::clearScene()
{
	_entityManager->removeRegistratedEntities();
}

GameEngine::~GameEngine()
{
	delete _masterInstance;
	delete _entityManager;

	_soundEngine->drop();
}

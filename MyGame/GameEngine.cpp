#include "GameEngine.h"


GameEngine::GameEngine(CIndieLib* _masterInstance)
	:_masterInstance(_masterInstance)
{
	_spriteCordinates = new SpriteCordinateMapper();
	_animationMapper = new AnimationMapper(_spriteCordinates);

	_entityManager = new GameEntityManager(_masterInstance, _spriteCordinates, _animationMapper, "D:/Vs2012 Project/C++ game development course/Sprite.png", mDelta);
}
void GameEngine::initialize()
{
	_spriteCordinates->loadSpriteMap("D:/Vs2012 Project/C++ game development course/Sprite.txt");
	_animationMapper->loadAnimationeMap("D:/Vs2012 Project/C++ game development course/Animations.txt");

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

	_entityManager->createAndAddEntity("HUD", HUDObject, Position3D(0, 0, 10), "orb + orb holder NEW");
	((HUD*)_entityManager->getEntity("HUD"))->setEntityToFollow((Ship*)_entityManager->getEntity("Ship"));

	_entityManager->drawEntities();

	_entityManager->getEntity("Ship")->setHotSpot(0.5f, 0.5f);

	_entityManager->setRectangleCollisionArea("Ship", 10, 35, 55, 70);
	_entityManager->setTriengleCollisionArea("Ship", Position2D(15, 35), Position2D(38, 3), Position2D(60, 35));

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
	_entityManager->update();
}

void GameEngine::processUserInput()
{
	Ship* ship = (Ship*)_entityManager->getEntity("Ship");

	if ((_masterInstance->_input->isKeyPressed(IND_ESCAPE))) //explosion 
	{
		_masterInstance->_render->endScene();
		_masterInstance->end();
		exit(0);
	}

	if ((_masterInstance->_input->isKeyPressed(IND_KEYLEFT))) //left
	{
		ship->rotateLeft(rotateSpeed);
		/*sound->play2D("../SpaceGame/resources/sound/flight.mp3", true);*/
	}

	if ((_masterInstance->_input->isKeyPressed(IND_KEYRIGHT))) //right
	{
		ship->rotateRight(rotateSpeed);
		/*sound->play2D("../SpaceGame/resources/sound/flight.mp3", true);*/
	}

	if ((_masterInstance->_input->isKeyPressed(IND_KEYUP))) //flying
	{
		accelerateShip(ship);
		/*sound->play2D("../SpaceGame/resources/sound/flight.mp3", true);*/	
	}
	else
	{
		deaccelerateShip(ship, -_accelerationStep);
	}

	if ((_masterInstance->_input->isKeyPressed(IND_KEYDOWN))) //flyingbackwards
	{
		deaccelerateShip(ship, _accelerationStep * 2);
		///*sound->play2D("../SpaceGame/resources/sound/flight.mp3", true);*/
	}

	if ((_masterInstance->_input->onKeyPress(IND_SPACE)))
	{
		ship->FireShoot();
	}
	if (_masterInstance->_input->isKeyPressed(IND_F12))
	{
		_entityManager->saveEntities("../save.js");
	}
	if (_masterInstance->_input->isKeyPressed(IND_F11))
	{
		_entityManager->loadEntityFromJSON("../save.js", mDelta);
	}
}
void GameEngine::accelerateShip(Ship* ship)
{
	if (!_reflect)
	{
		if (ship->isAnimationStoped())
			ship->startAnimation();

		ship->moveForward(_accelerationStep, true);
	}
	else
	{
		ship->moveBackward(_accelerationStep, true);
		if (ship->getAcceleration() <= 0)
			_reflect = false;
	}

}
void GameEngine::deaccelerateShip(Ship* ship, float accelerationStep)
{
	if (!_reflect)
	{
		ship->moveForward(accelerationStep, true);

		if (!ship->isAnimationStoped() && ship->getAcceleration() <= 0)
			ship->stopAnimation();
	}
	else
	{
		ship->moveBackward(_accelerationStep, true);
		if (ship->getAcceleration() <= 0)
			_reflect = false;
	}
}

void GameEngine::manageCollisions()
{
	if (_entityManager->checkForCollision("Ship", "Asteroid"))
	{
		_entityManager->removeEntity("Asteroid");
	}
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

			if (_entityManager->checkForCollision("Ship",it->first))
			{	
				ship->doDamage(it->second);
				ship->reflect();
				_reflect = true;

				ship->moveBackward(_accelerationStep, true);
			}
		}
	}
}

GameEngine::~GameEngine()
{
	delete _masterInstance;
	delete _entityManager;
}

#include "GameEngine.h"


GameEngine::GameEngine(CIndieLib* _masterInstance)
	:_masterInstance(_masterInstance)
{
	_spriteCordinates = new SpriteCordinateMapper();
	_animationMapper = new AnimationMapper(_spriteCordinates);

	_entityManager = new GameEntityManager(_masterInstance, _spriteCordinates, _animationMapper, "D:/Vs2012 Project/C++ game development course/Sprite.png");
}
void GameEngine::initialize()
{
	_spriteCordinates->loadSpriteMap("D:/Vs2012 Project/C++ game development course/Sprite.txt");
	_animationMapper->loadAnimationeMap("D:/Vs2012 Project/C++ game development course/Animations.txt");

	*mDelta = _masterInstance->_render->getFrameTime() / 1000.0f;

	_entityManager->createAndAddEntity("Ship", ShipObject, Position3D(600, 600, 3), "Ship", mDelta);
	_entityManager->createAndAddEntity("Space", StaticObject, Position3D(0, 0, 1), "background", mDelta);

	_entityManager->createAndAddEntity("Asteroid", SpaceBodyObject, Position3D(100, 200, 3), "asteroid", mDelta);
	_entityManager->createAndAddEntity("SmallPlanet", SpaceBodyObject, Position3D(250, 200, 3), "planet1", mDelta);
	_entityManager->createAndAddEntity("MediumPlanet", SpaceBodyObject, Position3D(450, 200, 3), "planet2", mDelta);

	_entityManager->createAndAddEntity("RedPlanet", SpaceBodyObject, Position3D(650, 200, 3), "planet3", mDelta);
	_entityManager->createAndAddEntity("BluePlanet", SpaceBodyObject, Position3D(800, 200, 3), "planet4", mDelta);

	_entityManager->drawEntities();

	Ship* ship = (Ship*)_entityManager->getEntity("Ship");

	ship->getINDIEntity()->setHotSpot(0.012f, 0.020f);
	_entityManager->setRectangleCollisionArea("Ship", 10, 35, 55, 70);
	_entityManager->setTriengleCollisionArea("Ship", Position2D(15, 35), Position2D(38, 3), Position2D(60, 35));

	_entityManager->setCircleCollisionArea("Asteroid", 72, 78, 60);

	_entityManager->setCircleCollisionArea("SmallPlanet", 100, 100, 73);
	_entityManager->setCircleCollisionArea("RedPlanet", 50, 50, 50);

	_entityManager->setCircleCollisionArea("MediumPlanet", 100, 101, 95);
	_entityManager->setCircleCollisionArea("BluePlanet", 110, 110, 96);

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
		if (ship->isAnimationStoped())
			ship->startAnimation();

		acc += _accelerationStep;
		if (acc > _maxAccelerationValue)
			acc = _maxAccelerationValue;

		ship->moveForward(acc, true);
		/*sound->play2D("../SpaceGame/resources/sound/flight.mp3", true);*/
	}
	else
	{
		if (acc > 0)
		{
			acc -= _accelerationStep;
			ship->moveForward(acc, true);
		}
		else
		{
			if (!ship->isAnimationStoped())
				ship->stopAnimation();
		}
	}

	if ((_masterInstance->_input->isKeyPressed(IND_KEYDOWN))) //flyingbackwards
	{

		if (acc > 0)
		{
			acc -= (_accelerationStep * 2);
			ship->moveForward(acc, true);
		}
		else
		{
			if (!ship->isAnimationStoped())
				ship->stopAnimation();
		}

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

		while (br < maxProjectiels)
		{
			if (_entityManager->getType(it->first) == SpaceBodyObject)
			{
				if (_entityManager->checkForCollision("Projectile", (*projectiles), it->first, it->second))
				{
					it->second->destroy();
					//_entityManager->removeEntity(it->first);
					(*projectiles)->destroy();
				}
			}

			*projectiles++;
			br++;
		}
	}
}

GameEngine::~GameEngine()
{
	delete _masterInstance;
	delete _entityManager;
}

#include "GameEngine.h"


GameEngine::GameEngine(CIndieLib* _masterInstance)
	:_masterInstance(_masterInstance)
{
	_spriteCordinates = new SpriteCordinateMapper();
	_animationMapper = new AnimationMapper(_spriteCordinates);

	_entityManager = new GameEntityManager(_masterInstance, _spriteCordinates, _animationMapper,"D:/Vs2012 Project/C++ game development course/Sprite.png");
}
void GameEngine::initialize()
{
	_spriteCordinates->loadSpriteMap("D:/Vs2012 Project/C++ game development course/Sprite.txt");
	_animationMapper->loadAnimationeMap("D:/Vs2012 Project/C++ game development course/Animations.txt");

	*mDelta = _masterInstance->_render->getFrameTime() / 1000.0f;

	_entityManager->createAndAddEntity("Ship", ShipObject, Position3D(600, 600, 3), "Ship", mDelta);
	_entityManager->createAndAddEntity("Space", StaticObject, Position3D(0, 0, 1), "galaxy", mDelta);

	_entityManager->createAndAddEntity("Asteroid", StaticObject, Position3D(100, 100, 3), "a2", mDelta);

	_entityManager->drawEntities();

	Ship* ship = (Ship*)_entityManager->getEntity("Ship");
	ship->getINDIEntity()->setHotSpot(0.05f, 0.145f);
	ship->getINDIEntity()->setScale(0.25f, 0.25f);

	_entityManager->setRectangleCollisionArea("Ship", 80, 120, 180, 350);
	_entityManager->setTriengleCollisionArea("Ship", Position2D(100, 120), Position2D(162, 0), Position2D(240, 120));

	_entityManager->setCircleCollisionArea("Asteroid", 160, 140, 120);
	_entityManager->setHotSpot("Asteroid", 0.05f, 0.075f);
}

void GameEngine::update()
{
	*mDelta = _masterInstance->_render->getFrameTime() / 1000.0f;
	_entityManager->update();
}

void GameEngine::processUserInput()
{
	//_entityManager->getEntity("Asteroid")->getINDIEntity()->setBoundingCircle("Asteroid", 100, 100, 100);
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
		}else
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
		}else
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
}

void GameEngine::manageCollisions()
{
	if (_entityManager->checkForCollision("Ship","Asteroid"))
	{
		//_entityManager->getEntity("Asteroid")->destroy();
	}
}

GameEngine::~GameEngine()
{
	delete _masterInstance;
	delete _entityManager;
}

#include "CIndieLib.h"
#include "IND_Surface.h"
#include "IND_Entity2d.h"
#include "GameEntity.h"
#include "ship.h"
#include "Space.h"
#include "Planet.h"
#include "IND_Animation.h"
#include "IND_AnimationManager.h"
#include "AnimatedGameEntity.h"
#include "GameEntityManager.h"
/*
==================
Main
==================
*/
const float _maxAccelerationValue = 600.f;
const float _accelerationStep = 1.f;

float rotation = 0;
float* mDelta = new float(0);
GameEntityManager* _gameEntityManager;

int IndieLib()
{
	//Sets the working path as the 'exe' directory. All resource paths are relative to this directory

	CIndieLib *mI = CIndieLib::instance();
	if (!mI->init()) return 0;

	_gameEntityManager = new GameEntityManager(mI);

	_gameEntityManager->createAndAddEntity("Ship", ShipObject, Position3D(600, 600, 3), "../SpaceGame/resources/animations/Spaceship.xml", mDelta);
	_gameEntityManager->createAndAddEntity("Space", StaticObject, Position3D(0, 0, 1), "../SpaceGame/resources/galaxy.jpg", mDelta);
	
	//_gameEntityManager->loadEntityFromJSON("../save.js", mDelta);

	_gameEntityManager->drawEntities();

	float mAngle = 0;
	float acc = 0.0f;
	

	float mPosX = 0;
	float mPosY = 0;
	int rotateSpeed = 200;

	Ship* ship = (Ship*)_gameEntityManager->getEntity("Ship");

	float mWidth = ship->getINDIEntity()->getRegionWidth() / 2;
	float mHeight = ship->getINDIEntity()->getRegionHeight() / 2;

	ship->getINDIEntity()->setHotSpot(0.5f, 0.5f);

	while (!mI->_input->onKeyPress(IND_ESCAPE) && !mI->_input->quit())  //idle
	{
		mI->_input->update();
		*mDelta = mI->_render->getFrameTime() / 1000.0f;

		if ((mI->_input->isKeyPressed(IND_ESCAPE))) //explosion 
		{
			ship->getINDIEntity()->setSequence(2);
			mI->_render->endScene();
			mI->end();
			exit(0);
		}

		if ((mI->_input->isKeyPressed(IND_KEYLEFT))) //left
		{
			ship->rotateLeft(rotateSpeed);
			/*sound->play2D("../SpaceGame/resources/sound/flight.mp3", true);*/
		}

		if ((mI->_input->isKeyPressed(IND_KEYRIGHT))) //right
		{
			ship->rotateRight(rotateSpeed);
			/*sound->play2D("../SpaceGame/resources/sound/flight.mp3", true);*/
		}

		if ((mI->_input->isKeyPressed(IND_KEYUP))) //flying
		{
			ship->getINDIEntity()->setSequence(1);

			acc += _accelerationStep;
			if (acc > _maxAccelerationValue)
				acc = _maxAccelerationValue;

			ship->moveForward(acc, true);

			/*sound->play2D("../SpaceGame/resources/sound/flight.mp3", true);*/
		}else
		{
			if (acc > 0)
			{
				acc -= _accelerationStep;
				ship->moveForward(acc, true);
				//TODO: Stop animation
			}
		}

		if ((mI->_input->isKeyPressed(IND_KEYDOWN))) //flyingbackwards
		{

			if (acc > 0)
			{
				acc -= (_accelerationStep * 2);
				ship->moveForward(acc, true);
				//TODO: Stop animation
			}

			///*sound->play2D("../SpaceGame/resources/sound/flight.mp3", true);*/
		}

		if ((mI->_input->onKeyPress(IND_SPACE)))
		{
			ship->FireShoot();
		}
		if (mI->_input->isKeyPressed(IND_F12))
		{
			_gameEntityManager->saveEntities("../save.js");
		}

		ship->Shooting();

		mI->_input->update();
		mI->_render->beginScene();
		mI->_entity2dManager->renderEntities2d();
		mI->_render->endScene();
	}

	//sound->drop();
	mI->end();

	return 0;
}

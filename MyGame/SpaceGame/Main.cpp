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
#include "GameEngine.h";
/*
==================
Main
==================
*/
const float _maxAccelerationValue = 600.f;
const float _accelerationStep = 0.1f;

float rotation = 0;
GameEngine* _engine;

int IndieLib()
{
	//Sets the working path as the 'exe' directory. All resource paths are relative to this directory

	CIndieLib *mI = CIndieLib::instance();
	if (!mI->init()) return 0;

	_engine = new GameEngine(mI);
	_engine->initialize();

	while (!mI->_input->onKeyPress(IND_ESCAPE) && !mI->_input->quit())  //idle
	{
		mI->_input->update();

		_engine->processUserInput();
		_engine->update();

		mI->_input->update();
		mI->_render->beginScene();

		mI->_entity2dManager->renderEntities2d();
		mI->_entity2dManager->renderCollisionAreas(255, 0, 0, 255);

		mI->_render->endScene();

		_engine->manageCollisions();
	}

	//sound->drop();
	mI->end();

	return 0;
}

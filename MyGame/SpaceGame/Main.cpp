#pragma comment(lib, "IPHLPAPI.lib")
#pragma comment(lib,"ws2_32.lib")

#define WIN32_LEAN_AND_MEAN        
#define _WINSOCK_DEPRECATED_NO_WARNINGS

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
#include "InstanceManager.h"
#include "ConfigurationReader.h"
/*
==================
Main
==================
*/
const float _maxAccelerationValue = 600.f;
const float _accelerationStep = 0.1f;

float rotation = 0;
GameEngine* _engine;
IND_Timer _firstInitializationTimer;

int IndieLib()
{
	//Executable path

	//Sets the working path as the 'exe' directory. All resource paths are relative to this directory

	//TCHAR NPath[MAX_PATH];
	//GetCurrentDirectory(MAX_PATH, NPath);

	//std::basic_string<TCHAR> strName = NPath;
	//new std::string(strName.c_str());

	//std::string path = "D:\Vs2012 Project\C++ game development course\ShipGame\GameDevelopmentC-Cource\MyGame\SpaceGame";

	//ConfigurationReader* reader = new ConfigurationReader((path + "\GameConfiguration.ini").c_str());
	//std::string token = reader->getSetting("Token");

	//InstanceManager* iM = new InstanceManager();
	//iM->getPlayer(token, iM->getMachineName());

	CIndieLib *mI = CIndieLib::instance();
	if (!mI->init()) return 0;

	_engine = new GameEngine(mI);

	_engine->initializeFonts();
	_engine->initializeEntities();

	_firstInitializationTimer.start();

	while (!mI->_input->onKeyPress(IND_ESCAPE) && !mI->_input->quit())  //idle
	{
		mI->_input->update();
		_engine->processUserInput();

		if (!_firstInitializationTimer.isStarted() || _firstInitializationTimer.getTicks() > 2)
		{
			_engine->manageCollisions();
		}
		else
		{
			if (_firstInitializationTimer.isStarted())
				_firstInitializationTimer.stop();
		}

		_engine->update();

		mI->_input->update();
		mI->_render->beginScene();

		mI->_entity2dManager->renderEntities2d();
		mI->_entity2dManager->renderCollisionAreas(255, 0, 0, 255);

		mI->_render->endScene();
		
	}

	//sound->drop();
	mI->end();

	return 0;
}

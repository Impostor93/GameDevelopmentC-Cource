//
///*****************************************************************************************
///* Desc: Tutorial a) 04 IND_Animation
///*****************************************************************************************/
//
//#include "CIndieLib.h"
//#include "IND_Surface.h"
//#include "IND_Entity2d.h"
//
//#include "IND_Surface.h"
//#include "IND_Animation.h"
//#include "IND_Entity2d.h"
//#include "IND_Animation.h"
//#include "IND_AnimationManager.h"
//
///*
//==================
//Main
//==================
//*/
//int IndieLib()
//{
//	// ----- IndieLib intialization -----
//
//	CIndieLib *mI = CIndieLib::instance();
//	if (!mI->init()) return 0;
//
//	// ----- Surface loading -----
//
//	// Loading Background
//	IND_Surface *mSurfaceBack = IND_Surface::newSurface();
//	if (!mI->_surfaceManager->add(mSurfaceBack, "../SpaceGame/resources/blue_background.jpg", IND_OPAQUE, IND_32)) return 0;
//
//	// ----- Animations loading -----
//
//	// Characters animations, we apply a color key of (0, 48, 152)
//	IND_Animation *mAnimationCharacter1 = IND_Animation::newAnimation();
//	if (!mI->_animationManager->addToSurface(mAnimationCharacter1, "../SpaceGame/resources/animations/character1.xml", IND_ALPHA, IND_32, 0, 48, 152)) return 0;
//
//	// Characters animations, we apply a color key of (0, 48, 152)
//	IND_Animation *mAnimationCharacter2 = IND_Animation::newAnimation();
//	if (!mI->_animationManager->addToSurface(mAnimationCharacter2, "../SpaceGame/resources/animations/character2.xml", IND_ALPHA, IND_32, 0, 48, 152)) return 0;
//
//	// Dust animation, we apply a color key of (255, 0, 255)
//	IND_Animation *mAnimationDust = IND_Animation::newAnimation();
//	if (!mI->_animationManager->addToSurface(mAnimationDust, "../SpaceGame/resources/animations/dust.xml", IND_ALPHA, IND_16, 255, 0, 255)) return 0;
//
//	// ----- Set the surface and animations into 2d entities -----
//
//	// Creating 2d entity for the background
//	IND_Entity2d *mBack = IND_Entity2d::newEntity2d();
//	mI->_entity2dManager->add(mBack);					// Entity adding
//	mBack->setSurface(mSurfaceBack);					// Set the surface into the entity
//
//	// Character 1
//	IND_Entity2d *mPlayer1 = IND_Entity2d::newEntity2d();
//	mI->_entity2dManager->add(mPlayer1);					// Entity adding
//	mPlayer1->setAnimation(mAnimationCharacter1);				// Set the animation into the entity
//
//	// Character 2
//	IND_Entity2d *mPlayer2 = IND_Entity2d::newEntity2d();
//	mI->_entity2dManager->add(mPlayer2);					// Entity adding
//	mPlayer2->setAnimation(mAnimationCharacter2);				// Set the animation into the entity
//
//	// Dust explosion
//	IND_Animation *mAnimationDust = IND_Animation::newAnimation();
//	if (!mI->_animationManager->addToSurface(mAnimationDust, "../SpaceGame/resources/animations/dust.xml", IND_ALPHA, IND_16, 255, 0, 255)) return 0;
//	IND_Entity2d *mDust = IND_Entity2d::newEntity2d();
//	mI->_entity2dManager->add(mDust);					// Entity adding
//	mDust->setAnimation(mAnimationDust);					// Set the animation into the entity
//
//	// ----- Changing the attributes of the 2d entities -----
//
//	// Player 1
//	mPlayer1->setSequence(0);						// Choose sequence
//	mPlayer1->setPosition(140, 200, 0);
//	mPlayer1->setMirrorX(1);						// Horizontal mirroring
//
//	// Dust explosion
//	mDust->setPosition(360, 250, 0);
//
//	// Player 2
//	mPlayer2->setSequence(0);						// Choose sequence
//	mPlayer2->setPosition(550, 200, 0);
//	mPlayer2->setNumReplays(3);						// The animation will be displayed 3 times
//
//	// ----- Main Loop -----
//
//	while (!mI->_input->onKeyPress(IND_ESCAPE) && !mI->_input->quit())
//	{
//		mI->_input->update();
//		mI->_render->beginScene();
//		mI->_entity2dManager->renderEntities2d();
//		mI->_render->endScene();
//	}
//
//	// ----- Free -----
//
//	mI->end();
//
//	return 0;
//}

/*****************************************************************************************
* Desc: Tutorial 02 IND_Surface
*****************************************************************************************/

#include "CIndieLib.h"
#include "IND_Surface.h"
#include "IND_Entity2d.h"
#include "GameEntity.h"
#include "Ship.h"
#include "Space.h"
#include "Planet.h"
#include "IND_Animation.h"
#include "IND_AnimationManager.h"
#include "AnimatedGameEntity.h"

/*
==================
Main
==================
*/
int IndieLib()
{
	//Sets the working path as the 'exe' directory. All resource paths are relative to this directory

	CIndieLib *mI = CIndieLib::instance();
	if (!mI->init()) return 0;

	AnimatedGameEntity* shipExplotion = new AnimatedGameEntity(mI, Position3D(0, 0, 1), "../SpaceGame/resources/animations/Ship_Explotion.xml");
	shipExplotion->Draw();

	//mDelta = mI->_render->getFrameTime() / 1000.0f;
	
	//ufo->setSequence(0);

<<<<<<< HEAD
	GameEntity* space = new Space(mI, Position3D(0, 0, 0), "../SpaceGame/resources/galaxy.jpg");
=======
	GameEntity* space = new Space(mI, Position3D(0, 0, 0), "../SpaceGame/resources/hubble-space-wallpapers.png");
>>>>>>> 4819329beea771722e09e466edd360c8f13e1970
	space->Draw();

	//GameEntity* planet1 = new Planet(mI, Position3D(0, 0, 1), "../SpaceGame/resources/a4203_planetes_g.png");
	//planet1->DrawRegion(new Region(100, 220, 140, 150));

	//GameEntity* planet2 = new Planet(mI, Position3D(300, 0, 1), "../SpaceGame/resources/a4203_planetes_g.png");
	//planet1->setPosition(Position3D(300, 0, 1));
	//planet1->DrawRegion(new Region(100, 220, 140, 150));

	//GameEntity* ship = new Ship(mI, Position3D(300, 200, 1), "../SpaceGame/resources/rocket.png");
	//ship->Draw();

	while (!mI->_input->onKeyPress(IND_ESCAPE) && !mI->_input->quit())
	{
		mI->_input->update();
		mI->_render->beginScene();
		mI->_entity2dManager->renderEntities2d();
		mI->_render->endScene();
	}

	mI->end();

	return 0;
}
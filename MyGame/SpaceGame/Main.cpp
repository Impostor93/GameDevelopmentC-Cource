#define _USE_MATH_DEFINES
#include <math.h>
#include "CIndieLib.h"
#include "IND_Surface.h"
#include "IND_Entity2d.h"
#include "IND_Font.h"
#include "GameEntity.h"
#include "Ship.h"
#include "Space.h"
#include "Planet.h"
#include "Main.h"
#include "IND_Animation.h"
#include "IND_AnimationManager.h"
#include "AnimatedGameEntity.h"
#include <IND_Sequence.h>
#include "Settings.h"
#include <windows.h>
#include <string>
#include <irrKlang.h>
#include "Projectile.h"

using namespace irrklang;
using namespace std;

//map<string, string> settings_;
//Settings* st = new Settings(settings_);
//void updateInput(CIndieLib* mI, AnimatedGameEntity *ship)
//{
//	if (mI->_input->onKeyPress(IND_K))
//	{
//		st->loadSettings("../SpaceGame/Config/settings.txt");
//		float x = stof(settings_["s_X"]);
//		float y = stof(settings_["s_Y"]);
//		ship->setPosition(x, y, 5);
//	}
//}

int IndieLib()
{
	CIndieLib *mI = CIndieLib::instance();
	if (!mI->init()) return 0;

	/*ISoundEngine* sound = createIrrKlangDevice();
	if (!sound) return 0;
	sound->play2D("../SpaceGame/resources/sound/smt.mp3", true);*/

	AnimatedGameEntity* ship = new AnimatedGameEntity(mI, Position3D(0, 0, 1), "../SpaceGame/resources/animations/Spaceship.xml");
	ship->Draw();

	GameEntity* space = new Space(mI, Position3D(0, 0, 0), "../SpaceGame/resources/galaxy.jpg");
	space->Draw();

	IND_Font* mFont = IND_Font::newFont();
	if (!mI->_fontManager->add(mFont, "../SpaceGame/resources/font_big.png", "../SpaceGame/resources/font_big.xml", IND_OPAQUE, IND_32)) return 0;

	IND_Entity2d* mText = IND_Entity2d::newEntity2d();
	mI->_entity2dManager->add(mText);

	mText->setFont(mFont);
	mText->setPosition(500, 100, 10);

	//GameEntity* planet1 = new Planet(mI, Position3D(0, 0, 1), "../SpaceGame/resources/a4203_planetes_g.png");
	//planet1->DrawRegion(new Region(100, 220, 140, 150));

	//GameEntity* planet2 = new Planet(mI, Position3D(300, 0, 1), "../SpaceGame/resources/a4203_planetes_g.png");
	//planet1->setPosition(Position3D(300, 0, 1));
	//planet1->DrawRegion(new Region(100, 220, 140, 150));

	//GameEntity* ship = new Ship(mI, Position3D(300, 200, 1), "../SpaceGame/resources/rocket.png");
	//ship->Draw();

	float acc = 1.0f;

	float mAngle = 0;
	float mPosX = 350;
	float mPosY = 250;
	int mSpeed = 250;
	float mDelta = 0.0f;
	char text[40];

	float mWidth = ship->getINDIEntity()->getRegionWidth() / 2;
	float mHeight = ship->getINDIEntity()->getRegionHeight()/ 2;
	ship->getINDIEntity()->setHotSpot(0.5f, 0.5f);

	
	while (!mI->_input->onKeyPress(IND_ESCAPE) && !mI->_input->quit())  //idle
	{
		//updateInput(mI, ship);
		mDelta = mI->_render->getFrameTime() / 1000.0f;
		mAngle = ship->getAngleZ();
		if (mPosX + mWidth >= mI->_window-> getWidth()) mPosX = mI->_window->getWidth();
		if (mPosX - mWidth< 0) mPosX = 0;
		if (mPosY + mHeight >= mI->_window->getHeight()) mPosY = mI->_window->getHeight();
		if (mPosY - mHeight < 0) mPosY = 0;
		if ((mI->_input->isKeyPressed(IND_D))) //explosion 
		{
			//ship->setSequence(2);
			//mI->_render->endScene();
			//mI->end();
			//exit(0);
		}

		


		if ((mI->_input->isKeyPressed(IND_KEYUP))) //flying
		{
			ship->setSequence(1);

			float angle = -ship->getAngleZ() + 90;

			acc += 0.1f;
			if (acc>10) acc = 10;
			float step = -(float)(100 * mDelta) * sin(angle / 180.0f * M_PI);

			sprintf(text, "%f", step);
			mText->setText(text);
			float x = 0.0f, y = 0.0f;
			float r = sqrt(float(ship->getPosX() * ship->getPosX() + ship->getPosY() * ship->getPosY()));
			x = ship->getPosX() + (1000 * mDelta) * cos(angle / 180.0f * M_PI);
			y = ship->getPosY() - (float)(1000 * mDelta) * sin(angle / 180.0f * M_PI);
			

			ship->setPosition(x, y, 0);
			//ship->setPosition(ship->getPosX(), y, 0);

			//mPosY -= mSpeed * mDelta;
			//ship->accelerate(mSpeed*(mDelta));
			/*sound->play2D("../SpaceGame/resources/sound/flight.mp3", true);*/
		}
		if ((mI->_input->isKeyPressed(IND_KEYLEFT))) //left
		{

			mAngle -= mSpeed * mDelta;
			ship->setAngleXYZ(0, 0, (float)mAngle);
			/*sound->play2D("../SpaceGame/resources/sound/flight.mp3", true);*/
		}



		if ((mI->_input->isKeyPressed(IND_KEYRIGHT))) //right
		{
			mAngle += mSpeed * mDelta;
			ship->setAngleXYZ(0, 0, (float)mAngle);
			/*sound->play2D("../SpaceGame/resources/sound/flight.mp3", true);*/
		}



		if ((mI->_input->isKeyPressed(IND_KEYDOWN))) //flyingbackwards
		{
			///*ship->setSequence(1);
			//ship->decelerate(mSpeed * (mDelta));*/
			//ship->setPosition(350, (float)mPosY, 5); //
			//mPosY += mSpeed * mDelta;
			///*sound->play2D("../SpaceGame/resources/sound/flight.mp3", true);*/
		}



		if ((mI->_input->isKeyPressed(IND_SPACE)))
		{
			Projectile* projectile = new Projectile(mI, Position3D(mPosX + 10.0f, mPosY + 10.0f, 5), "../SpaceGame/resources/projectile.png");
			projectile->Draw();
		}
		mI->_input->update();
		mI->_render->beginScene();
		mI->_entity2dManager->renderEntities2d();
		mI->_render->endScene();
	}

	//sound->drop();
	mI->end();

	return 0;
}

#include "AnimatedGameEntity.h"
using namespace std;

AnimatedGameEntity::AnimatedGameEntity(CIndieLib* masterInstance, Position3D position, const char* resourcePath)
	:GameEntity(masterInstance, position, resourcePath)
{
	_animation = IND_Animation::newAnimation();
	masterInstance->_animationManager->addToSurface(_animation, getResourcePath(), IND_ALPHA, IND_16);
	*accX = 1.0f;
	*accY = 1.0f;
	float innitalPosX = 0;
	float innitalPosY = 0;
	getINDIEntity()->setPosition((float)innitalPosX, (float)innitalPosY, 5);
}

void AnimatedGameEntity::Draw()
{	
	getINDIEntity()->setAnimation(_animation);
	getINDIEntity()->setHotSpot(0.5f, 0.5f);
	getINDIEntity()->setScale(0.32f,0.32f);
}


void AnimatedGameEntity::setSpeedX(float spX){*accX = spX;}
void AnimatedGameEntity::setSpeedY(float spY){*accY = spY;}

void AnimatedGameEntity::accelerate(float move)
{
	float angle = getINDIEntity()->getAngleZ()*PI/180.f;
	*accX = *accX + sin(angle)*move;
	*accY = *accY - cos(angle)*move;
}

void AnimatedGameEntity::decelerate(float move)
{
	float angle = getINDIEntity()->getAngleZ()*PI/180.f;
	*accX = *accX - sin(angle)*move;
	*accY = *accY + cos(angle)*move;
}

float AnimatedGameEntity::getPosX(){ return getINDIEntity()->getPosX(); }
float AnimatedGameEntity::getPosY(){ return getINDIEntity()->getPosY(); }

void AnimatedGameEntity::Destroy()
{
}

void AnimatedGameEntity::setSequence(int sequence)
{
	if(getINDIEntity())
		getINDIEntity()->setSequence(sequence);
}

void AnimatedGameEntity::setNumReplays(int numreplays)
{
	if (getINDIEntity())
		getINDIEntity()->setNumReplays(numreplays);
}

void AnimatedGameEntity::setAngleXYZ(float x, float y, float z)
{
	if (getINDIEntity())
		getINDIEntity()->setAngleXYZ(x, y, z);
}


void AnimatedGameEntity::setPosition(float x, float y, float z)
{
	if (getINDIEntity())
		getINDIEntity()->setPosition(x, y, z);
}

float AnimatedGameEntity::getAngleZ()
{
	return getINDIEntity()->getAngleZ();
}

AnimatedGameEntity::~AnimatedGameEntity()
{
	_animation = 0;
}
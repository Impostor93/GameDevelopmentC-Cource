#include "AnimatedGameEntity.h"

AnimatedGameEntity::AnimatedGameEntity(CIndieLib* masterInstance, Position3D position, const char* resourcePath, float* deltaTime)
	:GameEntity(masterInstance, position, resourcePath, deltaTime)
{
	_animation = IND_Animation::newAnimation();
}

void AnimatedGameEntity::draw()
{
	getMasterInstance()->_animationManager->addToSurface(_animation, getResourcePath(), IND_ALPHA, IND_16);
	getINDIEntity()->setAnimation(_animation);
	getINDIEntity()->setScale(0.15f,0.15f);
	getINDIEntity()->setPosition(getPosition().getX(), getPosition().getY(), getPosition().getZ());
}

void AnimatedGameEntity::destroy()
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


void AnimatedGameEntity::setPosition(Position3D position)
{
	_position = position;

	if (getINDIEntity())
		getINDIEntity()->setPosition(position.getX(), position.getY(), position.getZ());
}

AnimatedGameEntity::~AnimatedGameEntity()
{
	_animation = 0;
}
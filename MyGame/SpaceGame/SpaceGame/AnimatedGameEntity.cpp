#include "AnimatedGameEntity.h"


AnimatedGameEntity::AnimatedGameEntity(CIndieLib* masterInstance, Position3D position, const char* resourcePath)
	:GameEntity(masterInstance, position, resourcePath)
{
	_animation = IND_Animation::newAnimation();
	masterInstance->_animationManager->addToSurface(_animation, getResourcePath(), IND_ALPHA, IND_16, 255, 0, 255);
}

void AnimatedGameEntity::Draw()
{
	getINDIEntity()->setAnimation(_animation);
	getINDIEntity()->setPosition(getPosition().getX(), getPosition().getY(), getPosition().getZ());
}

void AnimatedGameEntity::Destroy()
{

}

void AnimatedGameEntity::setSequence(int sequence)
{
	if(getINDIEntity())
		getINDIEntity()->setSequence(sequence);
}

AnimatedGameEntity::~AnimatedGameEntity()
{
	_animation = 0;
}
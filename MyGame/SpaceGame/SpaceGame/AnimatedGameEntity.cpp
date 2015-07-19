#include "AnimatedGameEntity.h"


AnimatedGameEntity::AnimatedGameEntity(CIndieLib* masterInstance, Position3D position, const char* resourcePath)
	:GameEntity(masterInstance, position, resourcePath)
{
	_animation = IND_Animation::newAnimation();
<<<<<<< HEAD
	masterInstance->_animationManager->addToSurface(_animation, getResourcePath(), IND_ALPHA, IND_16);
=======
	masterInstance->_animationManager->addToSurface(_animation, getResourcePath(), IND_ALPHA, IND_16, 255, 0, 255);
>>>>>>> 4819329beea771722e09e466edd360c8f13e1970
}

void AnimatedGameEntity::Draw()
{
	getINDIEntity()->setAnimation(_animation);
<<<<<<< HEAD
	getINDIEntity()->setScale(0.15f,0.15f);
	getINDIEntity()->setPosition(340, 240, 5);//(getPosition().getX(), getPosition().getY(), getPosition().getZ());
=======
	getINDIEntity()->setPosition(getPosition().getX(), getPosition().getY(), getPosition().getZ());
>>>>>>> 4819329beea771722e09e466edd360c8f13e1970
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
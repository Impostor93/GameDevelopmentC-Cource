#include "SpaceBody.h"


SpaceBody::SpaceBody(CIndieLib* masterInstance, Position3D position, const char* path, IND_Surface* surface, AnimationMapper* animationMapper, float* deltaTime)
	: StaticGameEntity(masterInstance, position, path, surface, animationMapper->getSpriteCordinateMapper(), deltaTime)
{
	_explosion = new AnimatedGameEntity(masterInstance, position, "Explosion", surface, animationMapper, deltaTime);

	this->setDemageFactor(10);
	_hideSpaceBodyTimeoutTimer = new IND_Timer();
}

void SpaceBody::draw()
{
	StaticGameEntity::draw();
	_explosion->draw();

	float spaceObjectHeight = this->getINDIEntity()->getRegionHeight();
	float spaceObjectWidth = this->getINDIEntity()->getRegionWidth();

	float explosionHeight = _explosion->getINDIEntity()->getRegionHeight();
	float explosionWidth = _explosion->getINDIEntity()->getRegionWidth();

	float scaleX = spaceObjectWidth / explosionWidth;
	float scaleY = spaceObjectHeight / explosionHeight;

	_explosion->getINDIEntity()->setScale(scaleX, scaleY);
}
void SpaceBody::destroy()
{
	if (isBodyDestroyedAndExplosionFinished())
		SpaceBody::~SpaceBody();
}

void SpaceBody::update()
{
	if (_isDestroyed)
		_explosion->update();

	if (_health <= 0 && getINDIEntity()->isShow())
	{
		if (!_hideSpaceBodyTimeoutTimer->isStarted())
			_hideSpaceBodyTimeoutTimer->start();

		if (_hideSpaceBodyTimeoutTimer->getTicks() > 500)
		{
			this->getINDIEntity()->setShow(false);
			_hideSpaceBodyTimeoutTimer->stop();
		}
	}
	
	StaticGameEntity::update();
}
bool SpaceBody::isBodyDestroyedAndExplosionFinished()
{
	return (_health <= 0 && _explosion->isAnimationFinished());
}

void SpaceBody::doDamage()
{ 
	_health--; 
	if (_health <= 0)
	{
		_isDestroyed = true;
		_explosion->setNumReplays(1);
		Position3D newPos(_explosion->getPosition().getX(), _explosion->getPosition().getY(), _explosion->getPosition().getZ() + 5);
		_explosion->setPosition(newPos);
		_explosion->startAnimation();
	}
}

int SpaceBody::getHealth(){ return _health; }

SpaceBody::~SpaceBody()
{
	_explosion->destroy();

	delete _hideSpaceBodyTimeoutTimer;

	_hideSpaceBodyTimeoutTimer = 0;
	_explosion = 0;
}

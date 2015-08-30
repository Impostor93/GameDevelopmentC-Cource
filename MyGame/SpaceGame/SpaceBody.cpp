#include "SpaceBody.h"


SpaceBody::SpaceBody(CIndieLib* masterInstance, Position3D position, const char* path, IND_Surface* surface, AnimationMapper* animationMapper, float* deltaTime)
	: StaticGameEntity(masterInstance, position, path, surface, animationMapper->getSpriteCordinateMapper(), deltaTime)
{
	_explosion = new AnimatedGameEntity(masterInstance, position, "Explosion", surface, animationMapper, deltaTime);
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
	_isDestroyed = true;
	_explosion->setNumReplays(1);
	Position3D newPos(_explosion->getPosition().getX(), _explosion->getPosition().getY(), _explosion->getPosition().getZ() + 5);
	_explosion->setPosition(newPos);
	_explosion->startAnimation();
	StaticGameEntity::destroy();
}

void SpaceBody::update()
{
	if (_isDestroyed)
		_explosion->update();

	StaticGameEntity::update();
}

SpaceBody::~SpaceBody()
{
	delete _explosion;
	_explosion = 0;
}

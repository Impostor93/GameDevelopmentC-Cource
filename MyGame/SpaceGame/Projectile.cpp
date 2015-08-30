#include "Projectile.h"

Projectile::Projectile(CIndieLib* masterInstance, Position3D position, const char* path, IND_Surface* surface, SpriteCordinateMapper* spriteMapper, float* deltaTime)
	: StaticGameEntity(masterInstance, position, path, surface, spriteMapper, deltaTime)
{
}


Projectile::~Projectile()
{
}

void Projectile::setSpeed(float angle, float x, float y)
{
	_angleZ = angle;

	_speedX = x;
	_speedY = y;
}

void Projectile::moveForward(float acc, bool lockInWindowScreen)
{
	float tempX = this->getPosition().getX() + _speedX * acc;
	float tempY = this->getPosition().getY() + _speedY * acc;

	this->setPosition(Position3D(tempX, tempY, this->_position.getZ()));
}

void Projectile::draw()
{
	StaticGameEntity::draw();
	getINDIEntity()->setBoundingCircle("Projectile", 36, 23, 12);
}
void Projectile::update()
{
	GameEntity::update();
}

void Projectile::destroy()
{
	this->setPosition(Position3D(10000, 1000, this->getPosition().getZ()));
}

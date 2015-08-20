#include "Projectile.h"

Projectile::Projectile(CIndieLib* masterInstance, Position3D position, const char* path, IND_Surface* surface, SpriteCordinateMapper* spriteMapper, float* deltaTime)
	: StaticGameEntity(masterInstance, position, path, surface, spriteMapper, deltaTime)
{
}


Projectile::~Projectile()
{
}

void Projectile::setSpeed(float angle)
{
	_angleZ = angle;
	_speedX = std::sin(angle*3.14159265 / 180.f)* (*_deltaTime);
	_speedY = -std::cos(angle*3.14159265 / 180.f)* (*_deltaTime);
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
	getINDIEntity()->setBoundingCircle("projectile", 3, 3, 5);
}
void Projectile::update()
{
	GameEntity::update();
}

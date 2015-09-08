#include "Ship.h"

Ship::Ship(CIndieLib* masterInstance, Position3D position, std::string path, IND_Surface* surface, AnimationMapper* animationMapper, float* deltaTime)
	: AnimatedGameEntity(masterInstance, position, path, surface, animationMapper, deltaTime)
{
	
	for (int i = 0; i < maxProjectiels; i++)
	{
		_projectile[i] = new Projectile(masterInstance, Position3D(10000, 10000, this->getPosition().getZ() - 1)
				, "bullet", getSurface(), animationMapper->getSpriteCordinateMapper(), deltaTime);

		_projectile[i]->draw();
		_projectile[i]->setHotSpot(0.5f, 0.5f);
	}
}

Ship::~Ship()
{
}

void Ship::moveForward(float acceleration, bool lockInWindow)
{
	GameEntity::moveForward(acceleration, lockInWindow);
}
void Ship::update()
{
	AnimatedGameEntity::update();
	for (int i = 0; i < maxProjectiels; i++)
	{
		_projectile[i]->moveForward(projectileSpeed, false);
		_projectile[i]->update();
	}
}

void Ship::FireShoot()
{
	_shoots++;

	projectileIndex++;
	if (projectileIndex >= maxProjectiels)
	{
		projectileIndex = 0;
	}

	Projectile* projectile = _projectile[projectileIndex];
	int projectileRegion = projectile->getINDIEntity()->getRegionWidth();

	float angle = this->getINDIEntity()->getAngleZ()*3.14159265 / 180.f;
	float offsetX = _position.getX() + (float)std::sin(angle) * 30;
	float offsetY = _position.getY() - (float)std::cos(angle) * 30;

	projectile->setPosition(Position3D(offsetX, offsetY, projectile->getPosition().getZ()));

	float x = std::sin(angle) * (*_deltaTime);
	float y = -std::cos(angle) * (*_deltaTime);

	projectile->setSpeed(this->getINDIEntity()->getAngleZ(),x , y);
}

Projectile** Ship::getProjectiles(){ return _projectile; }

int Ship::getHealth(){ return _health; }
void Ship::doDamage(GameEntity* contactEntity){ _health -= contactEntity->getDemageFactor(); }
#include "Ship.h"

Ship::Ship(CIndieLib* masterInstance, Position3D position, const char* path, float* deltaTime) 
	: AnimatedGameEntity(masterInstance, position, path, deltaTime)
{
	
	for (int i = 0; i < maxProjectiels; i++)
	{
		_projectile[i] = new Projectile(masterInstance, Position3D(10000, 10000, _position.getZ() - 1)
										, "../SpaceGame/resources/projectile.png", deltaTime);
		_projectile[i]->draw();

	}
}

Ship::~Ship()
{
}

void Ship::moveForward(float acceleration, bool lockInWindow)
{
	GameEntity::moveForward(acceleration, lockInWindow);
}
void Ship::Shooting()
{
	for (int i = 0; i < maxProjectiels; i++)
	{
		_projectile[i]->moveForward(projectileSpeed, false);
	}
}

void Ship::FireShoot()
{
	//*shots += 1;

	projectileIndex++;
	if (projectileIndex > 9)
	{
		projectileIndex = 0;
	}

	float angle = this->getINDIEntity()->getAngleZ()*3.14159265 / 180.f;
	
	float offsetX = _position.getX() + std::sin(angle) * 20;
	float offsetY = _position.getY() - std::cos(angle) * 20;

	Projectile* projectile = _projectile[projectileIndex];

	projectile->setPosition(Position3D(offsetX, offsetY, projectile->getPosition().getZ()));
	projectile->getINDIEntity()->setAngleXYZ(0, 0, angle);
	projectile->setSpeed(this->getINDIEntity()->getAngleZ());
	projectile->getINDIEntity()->setBoundingCircle("projectile", 3, 3, 5);
}
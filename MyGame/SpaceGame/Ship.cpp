#include "Ship.h"

Ship::Ship(CIndieLib* masterInstance, Position3D position, std::string path, IND_Surface* surface, AnimationMapper* animationMapper, float* deltaTime)
	: AnimatedGameEntity(masterInstance, position, path, surface, animationMapper, deltaTime)
{
	
	for (int i = 0; i < maxProjectiels; i++)
	{
		_projectile[i] = new Projectile(masterInstance, Position3D(10000, 10000, this->getPosition().getZ() - 1)
				, "p2", getSurface(), animationMapper->getSpriteCordinateMapper(), deltaTime);

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
	//*shots += 1;

	projectileIndex++;
	if (projectileIndex >= maxProjectiels)
	{
		projectileIndex = 0;
	}

	float angle = this->getINDIEntity()->getAngleZ()*3.14159265 / 180.f;
	
	float offsetX = _position.getX() + std::sin(angle) * 40;
	float offsetY = _position.getY() - std::cos(angle) * 40;

	Projectile* projectile = _projectile[projectileIndex];

	int projectileRegion = projectile->getINDIEntity()->getRegionWidth();

	int regionWidth = this->getINDIEntity()->getRegionWidth();
	float a = regionWidth * 0.25f;

	float midleOFShipX = (a / 2) + projectileRegion * 0.05;

	projectile->setPosition(Position3D(_position.getX() - midleOFShipX, offsetY, projectile->getPosition().getZ()));
	projectile->getINDIEntity()->setAngleXYZ(0, 0, angle);

	projectile->setSpeed(this->getINDIEntity()->getAngleZ());
}

Projectile** Ship::getProjectiles(){ return _projectile; }
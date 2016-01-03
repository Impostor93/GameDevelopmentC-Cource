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

	_shipState = Peace;
	_reloeadBulletTimer = new IND_Timer();
}

Ship::~Ship()
{
	delete _projectile;
}

void Ship::moveForward(float acceleration, bool lockInWindow)
{
	GameEntity::moveForward(acceleration, lockInWindow);
}
Position2D Ship::calcuateNewPositionOnMovingForward()
{
	if (_shipState != Soar && _shipState != ReflectBack && _shipState != ReflectFront)
		_angle = this->getINDIEntity()->getAngleZ();

	float x = 0.f; x = this->getPosition().getX() + (getAcceleration() * (*_deltaTime)) *(float)sin(_angle / 180.f * PI);
	float y = 0.f; y = this->getPosition().getY() - (getAcceleration() * (*_deltaTime)) *(float)cos(_angle / 180.f * PI);

	return Position2D(x, y);
}

void Ship::moveBackward(float acceleration, bool lockInWindow)
{
	GameEntity::moveBackward(acceleration, lockInWindow);
} 
Position2D Ship::calcuateNewPositionOnMovingBackward()
{
	if (_shipState != Soar && _shipState != ReflectBack && _shipState != ReflectFront)
		_angle = this->getINDIEntity()->getAngleZ();

	float x = this->getPosition().getX() - (getAcceleration() * (*_deltaTime)) * (float)sin(_angle / 180.f * PI);
	float y = this->getPosition().getY() + (getAcceleration() * (*_deltaTime)) * (float)cos(_angle / 180.f * PI);

	return Position2D(x, y);
}

void Ship::update()
{
	AnimatedGameEntity::update();
	for (int i = 0; i < maxProjectiels; i++)
	{
		_projectile[i]->moveForward(projectileSpeed, false);
		_projectile[i]->update();
	}
	if (_shoots >= 99)
	{
		if(!_reloeadBulletTimer->isStarted())
			_reloeadBulletTimer->start();

		if (_reloeadBulletTimer->getTicks() >= 1000 * _reloadTimeInSeconds){
			_shoots = 0;
			_reloeadBulletTimer->stop();
		}
	}
}

void Ship::FireShoot()
{
	if (_shoots >= 99)
		return;

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
int Ship::getShootCount(){ return _shoots; }
std::string Ship::getShootTimerTicks(){ return !_reloeadBulletTimer->isStarted() ? "" : Common::IntToString(_reloadTimeInSeconds - (_reloeadBulletTimer->getTicks() / 1000)); }

void Ship::doDamage(GameEntity* contactEntity){ if (_health > 0){ _health -= contactEntity->getDemageFactor(); } }

void Ship::changeState(ShipState shipState){ _shipState = shipState; }
void Ship::changeShipRotationState(ShipRotationState newState){ _shipRotateState = newState; }
ShipState Ship::getState(){ return _shipState; }
ShipRotationState Ship::getShipRotateState(){ return _shipRotateState; }

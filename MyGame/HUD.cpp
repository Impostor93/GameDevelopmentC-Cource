#include "HUD.h"


HUD::HUD(CIndieLib* masterInstance, Position3D position, std::string resource, IND_Surface* surface, SpriteCordinateMapper* spriteMapper, float* deltaTime)
	:StaticGameEntity(masterInstance, position, resource, surface, spriteMapper, deltaTime)
{
	_healthBarImages = { "red reversed 6", "red reversed 5", "red reversed 4", "red reversed 3", "red reversed 2", "red reversed 1", "red reversed all" };

	_healthBar = new StaticGameEntity(masterInstance, Position3D(10000, 10000, position.getZ()),
		"red reversed all", surface, spriteMapper, deltaTime);

	_shootBar = new StaticGameEntity(masterInstance, Position3D(10000, 10000, position.getZ()),"orange reversed all", surface, spriteMapper, deltaTime);
}

void HUD::setEntityToFollow(Ship* ship)
{
	_ship = ship;
}

void HUD::draw()
{
	StaticGameEntity::draw();

	_healthBar->draw();
	_shootBar->draw();

	float windowHeight = getMasterInstance()->_window->getHeight();
	float windowWidth = getMasterInstance()->_window->getWidth();
	float scaleFactor = 0.40f;

	this->setPosition(Position3D(windowWidth / 2 - (getINDIEntity()->getRegionWidth()*0.5f) / 2, 0, this->getPosition().getZ()));

	this->getINDIEntity()->setScale(0.5f, 0.50f);

	float y = windowHeight - (_healthBar->getINDIEntity()->getRegionHeight() * scaleFactor);

	_healthBar->setPosition(Position3D(0, y, this->getPosition().getZ()));

	float x = windowWidth - _shootBar->getINDIEntity()->getRegionWidth() * scaleFactor;
	_shootBar->setPosition(Position3D(x, y, this->getPosition().getZ()));

	_healthBar->getINDIEntity()->setScale(scaleFactor, scaleFactor);
	_shootBar->getINDIEntity()->setScale(scaleFactor, scaleFactor);
}
void HUD::update()
{
	StaticGameEntity::update();

	std::string resource = "red reversed all";
	float persent = 100 / _healthSectionsCount;

	for (int i = _healthSectionsCount-1; i >= 0; i--)
	{
		if (_ship->getHealth() < (i + 1) * persent)
			resource = _healthBarImages.at(i);
	}

	_healthBar->changeResource(resource);
	_healthBar->update();

	_shootBar->update();
	//_shootBar->changeResource(getResourcePath());
}

void HUD::destroy()
{
}

HUD::~HUD()
{
}

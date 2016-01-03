#include "HUD.h"

HUD::HUD(CIndieLib* masterInstance, Position3D position, std::string resource, IND_Surface* surface, SpriteCordinateMapper* spriteMapper, float* deltaTime)
	:StaticGameEntity(masterInstance, position, resource, surface, spriteMapper, deltaTime)
{
	_healthBarFont = new Font(masterInstance, position, "../SpaceGame/resources/font_small.png","../SpaceGame/resources/font_small.xml", deltaTime);
	_shootBarFont = new Font(masterInstance, position, _healthBarFont->getINDIFont(), deltaTime);
	_reloadingFont = new Font(masterInstance, position, _healthBarFont->getINDIFont(), deltaTime);
	
	_healthBarImages = { "red reversed 6", "red reversed 5", "red reversed 4", "red reversed 3", "red reversed 2", "red reversed 1", "red reversed all" };

	_healthBar = new StaticGameEntity(masterInstance, Position3D(10000, 10000, position.getZ()),
		"red reversed all", surface, spriteMapper, deltaTime);

	_shootBarImages = { "orange reversed 1", "orange reversed 2", "orange reversed 3", "orange reversed 4", "orange reversed 5", "orange reversed 6", "orange reversed all" };
	_shootBar = new StaticGameEntity(masterInstance, Position3D(10000, 10000, position.getZ()),"orange reversed all", surface, spriteMapper, deltaTime);
}
HUD::~HUD()
{
	delete _healthBar;
	delete _shootBar;
	delete _healthBarFont;
	delete _shootBarFont;
	delete _reloadingFont;

	_healthBar = 0;
	_shootBar = 0;
	_healthBarFont = 0;
	_shootBarFont = 0;
	_reloadingFont = 0;
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

	_healthBarFont->draw();
	_healthBarFont->getINDIEntity()->setAlign(IND_LEFT);

	_shootBarFont->draw();
	_shootBarFont->getINDIEntity()->setAlign(IND_LEFT);

	_reloadingFont->draw();
	_reloadingFont->getINDIEntity()->setAlign(IND_LEFT);

	float windowHeight = getMasterInstance()->_window->getHeight();
	float windowWidth = getMasterInstance()->_window->getWidth();

	this->setPosition(Position3D(windowWidth / 2 - (getINDIEntity()->getRegionWidth()*0.5f) / 2, 0, this->getPosition().getZ()));

	this->getINDIEntity()->setScale(0.5f, 0.50f);

	float y = windowHeight - (_healthBar->getINDIEntity()->getRegionHeight() * _scaleFactor);
	_healthBar->setPosition(Position3D(0, y, this->getPosition().getZ()));

	float x = windowWidth - _shootBar->getINDIEntity()->getRegionWidth() * _scaleFactor;
	_shootBar->setPosition(Position3D(x, y, this->getPosition().getZ()));
	_shootBarFont->setPosition(Position3D(x, y, this->getPosition().getZ()+1));

	_healthBar->getINDIEntity()->setScale(_scaleFactor, _scaleFactor);
	_shootBar->getINDIEntity()->setScale(_scaleFactor, _scaleFactor);
}
void HUD::update()
{
	StaticGameEntity::update();

	std::string resource = "red reversed all";
	float healthSections = 100 / _healthSectionsCount;

	for (int i = _healthSectionsCount-1; i >= 0; i--)
	{
		if (_ship->getHealth() < (i + 1) * healthSections)
			resource = _healthBarImages.at(i);
	}

	_healthBar->changeResource(resource);
	_healthBar->update();

	resource = "orange reversed all";
	float bulletSection = 100 / _bulletSectionsCount;
	for (int i = 0; i < _bulletSectionsCount; i++)
	{
		if (_ship->getShootCount() > (i + 2) * bulletSection)
			resource = _shootBarImages.at(i);
	}

	_shootBar->changeResource(resource);
	_shootBar->update();

	_healthBarFont->setText(Common::IntToString(_ship->getHealth()));
	_shootBarFont->setText(Common::IntToString(_ship->getShootCount()));
	_reloadingFont->setText(_ship->getShootTimerTicks());

	updateHealthBarPosition();
	updateShootBarPosition();
	updateShootTimerBarPosition();

	_healthBarFont->update();
	_shootBarFont->update();
	_reloadingFont->update();
}

void HUD::updateHealthBarPosition()
{
	int charWith = 16;//Comes from XML and I am not able to get it dynamically  

	int width = _healthBar->getINDIEntity()->getRegionWidth();
	std::string text = _healthBarFont->getINDIEntity()->getText();
	int xOfFont = ((width * _scaleFactor * 0.5f) / 2 - (text.length() * charWith) / 2) + 5;

	_healthBarFont->setPosition(Position3D(xOfFont, _healthBar->getPosition().getY() + 32, this->getPosition().getZ() + 1));
}
void HUD::updateShootBarPosition()
{
	int charWith = 16;//Comes from XML and I am not able to get it dynamically  

	int width = _shootBar->getINDIEntity()->getRegionWidth();
	std::string text = _shootBarFont->getINDIEntity()->getText();
	int xOfFont = ((width * _scaleFactor) / 2 - (text.length() * charWith) / 2) + 40;

	_shootBarFont->setPosition(Position3D(_shootBar->getPosition().getX() + xOfFont, _shootBar->getPosition().getY() + 32, this->getPosition().getZ() + 1));
}
void HUD::updateShootTimerBarPosition()
{
	int charWith = 16;//Comes from XML and I am not able to get it dynamically  

	int width = this->getINDIEntity()->getRegionWidth();
	std::string text = _reloadingFont->getINDIEntity()->getText();
	int xOfFont = ((width * _scaleFactor) / 2 - (text.length() * charWith) / 2) + 32;

	_reloadingFont->setPosition(Position3D(this->getPosition().getX() + xOfFont, this->getPosition().getY() + 15, this->getPosition().getZ() + 1));
}


void HUD::destroy()
{
	HUD::~HUD();
}

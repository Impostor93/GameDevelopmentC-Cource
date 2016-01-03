#include "Font.h"


Font::Font(CIndieLib* masterInstance, Position3D position, std::string fondImages, std::string xmlResource, float* deltaTime)
	:GameEntity(masterInstance, position, fondImages, IND_Surface::newSurface(), deltaTime), _xmlResource(xmlResource)
{
	_indFont = IND_Font::newFont();
	
	getMasterInstance()->_fontManager->add(_indFont, fondImages.c_str(), xmlResource.c_str(), IND_ALPHA, IND_32);
}
Font::Font(CIndieLib* masterInstance, Position3D position, IND_Font* font, float* deltaTime)
	:GameEntity(masterInstance, position, "", IND_Surface::newSurface(), deltaTime), _indFont(font)
{
}

void Font::draw()
{
	this->getINDIEntity()->setFont(this->_indFont);
}
void Font::update()
{
	getINDIEntity()->setText(_text.c_str());
	getINDIEntity()->setPosition(getPosition().getX(), getPosition().getY(), getPosition().getZ());
	getINDIEntity()->setAlign(IND_LEFT);
	getINDIEntity()->setTint(120, 120, 120);
}

void Font::setText(std::string text)
{
	_text = text;
}
IND_Font* Font::getINDIFont(){ return _indFont; }

void Font::destroy()
{
	Font::~Font();
}

std::string Font::getXMLReource(){ return _xmlResource; }

Font::~Font()
{
	_indFont->destroy();
}

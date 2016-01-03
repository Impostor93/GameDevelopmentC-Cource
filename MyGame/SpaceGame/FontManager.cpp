#include "FontManager.h"


FontManager::FontManager(CIndieLib* indiMasterInstance, float* deltaTime):
_indiMasterInstance(indiMasterInstance), _deltaTime(deltaTime)
{
	
}

void FontManager::addIndiFont(std::string key, std::string imagePath, std::string xmlResource)
{
	_indiFonts.insert(pair<std::string, IND_Font*>(key, IND_Font::newFont()));
	_indiMasterInstance->_fontManager->add(getIndiFont(key), imagePath.c_str(), xmlResource.c_str(), IND_ALPHA, IND_32);
}

void FontManager::createFontInstance(std::string key, std::string fontName, Position3D position)
{
	_fonts.insert(pair<std::string,Font*>(key, new Font(_indiMasterInstance, position, _indiFonts.at(fontName), _deltaTime)));
}

void FontManager::draw()
{
	for (std::map<std::string, Font*>::iterator it = _fonts.begin(); it != _fonts.end(); ++it)
		it->second->draw();
}
void FontManager::update()
{
	for (std::map<std::string, Font*>::iterator it = _fonts.begin(); it != _fonts.end(); ++it)
		it->second->update();
}

Font* FontManager::getFont(std::string key)
{ 
	if (_fonts.count(key) <= 0)
		throw "There is no font with key " + key;

	return _fonts.at(key); 
}

void FontManager::setText(std::string key, std::string text)
{
	this->getFont(key)->setText(text.c_str());
}
void FontManager::setPosition(std::string key, Position3D position) 
{
	this->getFont(key)->setPosition(position);
}

IND_Font* FontManager::getIndiFont(std::string name)
{
	if (_indiFonts.count(name) <= 0)
		throw "There is no font with name " + name;

	return _indiFonts.at(name);
}

FontManager::~FontManager()
{
	for (std::map<std::string, Font*>::iterator it = _fonts.begin(); it != _fonts.end(); ++it)
		it->second->destroy();

	for (std::map<std::string, IND_Font*>::iterator it = _indiFonts.begin(); it != _indiFonts.end(); ++it)
		it->second->destroy();

	delete _indiMasterInstance;
	delete _deltaTime;
}

#pragma once

#ifndef FontManager_H
#define FontManager_H

#include <map>
#include "CIndieLib.h"
#include "IND_Entity2d.h"
#include "IND_SurfaceManager.h"
#include "IND_Surface.h"
#include "IND_Font.h"
#include "Position3D.h"
#include "Font.h"

class FontManager
{
private:
	map<std::string, IND_Font*> _indiFonts;
	map<std::string, Font*> _fonts;

	CIndieLib* _indiMasterInstance;
	float* _deltaTime;
public:
	FontManager(CIndieLib* indiMasterInstance, float* deltaTime);
	~FontManager();

	void addIndiFont(std::string name, std::string imagePath, std::string xmlResource);

	void createFontInstance(std::string key, std::string fontName, Position3D position);
	void setText(std::string key, std::string text);
	void setPosition(std::string key, Position3D position);
	Font* getFont(std::string key);
	IND_Font* getIndiFont(std::string name);
	
	void update();
	void draw();
};

#endif
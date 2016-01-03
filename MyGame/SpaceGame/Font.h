#pragma once

#ifndef FONT_H
#define FONT_H

#include "GameEntity.h"
#include "IND_Font.h"

class Font: public GameEntity
{
public:
	Font(CIndieLib* masterInstance, Position3D position, std::string resourcePath, std::string xmlResource, float* deltaTime);
	Font(CIndieLib* masterInstance, Position3D position, IND_Font* font, float* deltaTime);
	~Font();

	void draw();
	void update();
	void destroy();

	std::string getXMLReource();

	void setText(std::string text);
	IND_Font* getINDIFont();

private:
	IND_Font *_indFont;
	std::string _xmlResource;
	std::string _text;
};

#endif


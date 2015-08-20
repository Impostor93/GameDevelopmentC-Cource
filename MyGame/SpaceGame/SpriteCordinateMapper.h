#pragma once
#ifndef SPRITECORDINATEMAPPER
#define SPRITECORDINATEMAPPER

#include <string>
#include <fstream>

#include <map>
#include "Region.h"
#include "Common.h"


class SpriteCordinateMapper
{
private:
	std::map<std::string, Region> _spriteRegions;

public:
	SpriteCordinateMapper();
	~SpriteCordinateMapper();

	void loadSpriteMap(std::string fileName);
	Region getSpriteRegionByName(std::string name);
};

#endif
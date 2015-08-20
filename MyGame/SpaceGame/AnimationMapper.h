#pragma once
#ifndef ANIMATIONMAPPER
#define ANIMATIONMAPPER

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "StaticGameEntity.h"
#include "Region.h"
#include "Frame.h"
#include "Common.h"
#include "SpriteCordinateMapper.h"

class AnimationMapper
{
private:
	std::map<std::string, std::vector<Frame>> _animationFrames;
	SpriteCordinateMapper* _spriteCordinateMapper;

public:
	AnimationMapper(SpriteCordinateMapper* spriteCordinateMapper);
	~AnimationMapper();

	void loadAnimationeMap(std::string fileName);
	std::vector<Frame> getAnimationByName(std::string name);

	SpriteCordinateMapper* getSpriteCordinateMapper();
};

#endif
#pragma once

#ifndef HUD_H
#define HUD_H

#include "GameEntity.h"
#include "IndieLib.h"
#include "SpriteCordinateMapper.h"
#include "Ship.h"

class HUD : public StaticGameEntity
{
private: 
	Ship* _ship;
	StaticGameEntity* _healthBar;
	StaticGameEntity* _shootBar;

	int const _healthSectionsCount = 7;
	const int _bulletSectionsCount = 7;

	std::vector<std::string> _healthBarImages;

public:
	HUD(CIndieLib* masterInstance, Position3D position, std::string resource, IND_Surface* surface, SpriteCordinateMapper* spriteMapper, float* deltaTime);
	~HUD();

	void setEntityToFollow(Ship* ship);

	void draw();
	void destroy();
	void update();
};

#endif
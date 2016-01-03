#pragma once
#ifndef SPACEBODY
#define SPACEBODY

#include "StaticGameEntity.h"
#include "AnimationMapper.h"
#include "AnimatedGameEntity.h"

class SpaceBody : public StaticGameEntity
{
private:
	AnimatedGameEntity* _explosion;
	bool _isDestroyed = false;
	int _health = 5;
	IND_Timer* _hideSpaceBodyTimeoutTimer;
	int _hideSpaceBodyTimeoutInMS = 500;
public:
	SpaceBody(CIndieLib* masterInstance, Position3D position, const char* path, IND_Surface* surface, AnimationMapper* spriteMapper, float* deltaTime);
	~SpaceBody();

	void destroy();
	void update();
	void draw();

	void doDamage();

	bool isBodyDestroyedAndExplosionFinished();
	int getHealth();
};

#endif // !SpaceBody
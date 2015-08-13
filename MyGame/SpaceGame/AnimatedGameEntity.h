#pragma once
#ifndef ANIMATEDGAMEENTITY_H
#define ANIMATEDGAMEENTITY_H

#include "GameEntity.h"
#include "IND_Animation.h"

class AnimatedGameEntity : public GameEntity
{
public:
	AnimatedGameEntity(CIndieLib* masterInstance, Position3D position, const char* resourcePath, float* deltaTime);
	~AnimatedGameEntity();
	
	void draw();
	void destroy();
	void setSequence(int sequence);
	void setNumReplays(int numreplays);
	void setAngleXYZ(float x, float y, float z);
	void setPosition(Position3D position);

private:
	IND_Animation* _animation = 0;
};

#endif

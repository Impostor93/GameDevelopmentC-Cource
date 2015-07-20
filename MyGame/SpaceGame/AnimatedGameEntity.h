#pragma once
#include "GameEntity.h"
#include "IND_Animation.h"

class AnimatedGameEntity : public GameEntity
{
public:
	AnimatedGameEntity(CIndieLib* masterInstance, Position3D position, const char* resourcePath);
	~AnimatedGameEntity();
	
	void Draw();
	void Destroy();
	void setSequence(int sequence);
	void setNumReplays(int numreplays);

private:
	IND_Animation* _animation = 0;
};


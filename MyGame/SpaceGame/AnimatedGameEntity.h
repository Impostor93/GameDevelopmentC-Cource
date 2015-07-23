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
	void setAngleXYZ(float x, float y, float z);
	void setPosition(float x, float y, float z);

private:
	IND_Animation* _animation = 0;
};


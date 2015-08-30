#pragma once
#ifndef ANIMATEDGAMEENTITY_H
#define ANIMATEDGAMEENTITY_H

#include "GameEntity.h"
#include "AnimationMapper.h"
#include "Frame.h"

class AnimatedGameEntity : public GameEntity
{
public:
	AnimatedGameEntity(CIndieLib* masterInstance, Position3D position, std::string resourcePath, IND_Surface* surface, AnimationMapper* animationMapper, float* deltaTime);
	~AnimatedGameEntity();
	
	void draw();
	void destroy();
	void setSequence(int sequence);
	void setNumReplays(int numreplays);
	void setAngleXYZ(float x, float y, float z);
	void setPosition(Position3D position);

	void stopAnimation();
	void startAnimation();
	bool isAnimationStoped();
	AnimationMapper* getAnimationMapper();

	void update();
private:
	AnimationMapper* _animationMapper = 0;
	std::vector<Frame>* _animationFrame;

	Frame* _frame = 0;
	Region* _region = 0;

	int _animationCurrentIndex = 0;

	IND_Timer* _timer = 0;

	bool _isAnimationStoped = true;

	int _currentNumberOfReplay = 0;
	int _numberOfReplay = -1;
};

#endif

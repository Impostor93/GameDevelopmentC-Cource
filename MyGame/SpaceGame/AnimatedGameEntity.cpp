#include "AnimatedGameEntity.h"

AnimatedGameEntity::AnimatedGameEntity(CIndieLib* masterInstance, Position3D position, std::string resourcePath, IND_Surface* surface, AnimationMapper* animationMapper, float* deltaTime)
	:GameEntity(masterInstance, position, resourcePath, surface, deltaTime)
{
	_animationMapper = animationMapper;
	_animationFrame = new std::vector<Frame>(_animationMapper->getAnimationByName(resourcePath));
	_timer = new IND_Timer();
}

void AnimatedGameEntity::draw()
{
	getINDIEntity()->setSurface(getSurface());

	_frame = new Frame(_animationFrame->at(_animationCurrentIndex));
	_region = new Region(_frame->getRegionOfFrame());

	getINDIEntity()->setRegion(_region->getOffSetX(), _region->getOffSetY(), _region->getWidth(), _region->getHeight());
}

void AnimatedGameEntity::destroy()
{

}
void AnimatedGameEntity::update()
{
	GameEntity::update();

	getINDIEntity()->setAngleXYZ(getINDIEntity()->getAngleX(), getINDIEntity()->getAngleY(), _angleZ);

	if (!_isAnimationStoped && _timer->getTicks() >= _frame->getTime())
	{
		_animationCurrentIndex++;
		_timer->start();//restart
	}

	if (_animationCurrentIndex >= _animationFrame->size())
	{
		_animationCurrentIndex = 0;
		_currentNumberOfReplay++;
	}

	if (_numberOfReplay != -1 && _currentNumberOfReplay >= _numberOfReplay)
		this->stopAnimation();

	_frame = &_animationFrame->at(_animationCurrentIndex);
	_region = &_frame->getRegionOfFrame();

	getINDIEntity()->setRegion(_region->getOffSetX(), _region->getOffSetY(), _region->getWidth(), _region->getHeight());
}

void AnimatedGameEntity::startAnimation()
{
	_isAnimationStoped = false;
	_timer->start();
}
void AnimatedGameEntity::stopAnimation()
{
	_isAnimationStoped = true;
	_animationCurrentIndex = 0;
	_timer->stop();
}

bool AnimatedGameEntity::isAnimationStoped(){ return _isAnimationStoped; }

AnimationMapper* AnimatedGameEntity::getAnimationMapper(){ return _animationMapper; }

void AnimatedGameEntity::setNumReplays(int numreplays)
{
	_numberOfReplay = numreplays;
}

void AnimatedGameEntity::setAngleXYZ(float x, float y, float z)
{
	if (getINDIEntity())
		getINDIEntity()->setAngleXYZ(x, y, z);
}

void AnimatedGameEntity::setPosition(Position3D position)
{
	_position = position;

	//if (getINDIEntity())
	//	getINDIEntity()->setPosition(position.getX(), position.getY(), position.getZ());
}

AnimatedGameEntity::~AnimatedGameEntity()
{
	delete _frame;
	delete _region;
	delete _animationFrame;
	delete _timer;

	_timer = 0;
	_animationFrame = 0;
	_region = 0;
	_frame = 0;
}
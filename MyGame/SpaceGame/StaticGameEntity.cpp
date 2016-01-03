#include "StaticGameEntity.h"


StaticGameEntity::StaticGameEntity(CIndieLib* masterInstance, Position3D position, std::string resource, IND_Surface* surface, SpriteCordinateMapper* spriteMapper, float* deltaTime)
	:GameEntity(masterInstance, position, resource, surface, deltaTime)
{
	_spriteMapper = spriteMapper;
}

void StaticGameEntity::draw()
{
	this->getINDIEntity()->setSurface(getSurface());
	Region regionOfEntity = _spriteMapper->getSpriteRegionByName(getResourcePath());
	this->getINDIEntity()->setRegion(regionOfEntity.getOffSetX(), regionOfEntity.getOffSetY(), regionOfEntity.getWidth(), regionOfEntity.getHeight());
}

void StaticGameEntity::destroy()
{
	if (getINDIEntity() != NULL)
		StaticGameEntity::~StaticGameEntity();
}

void StaticGameEntity::update()
{
	GameEntity::update();
	getINDIEntity()->setAngleXYZ(getINDIEntity()->getAngleX(), getINDIEntity()->getAngleY(), _angleZ);

	Region region = this->_spriteMapper->getSpriteRegionByName(getResourcePath());
	getINDIEntity()->setRegion(region.getOffSetX(), region.getOffSetY(), region.getWidth(), region.getHeight());
}

void StaticGameEntity::changeResource(std::string resource)
{
	this->setResourcePath(resource);
}

StaticGameEntity::~StaticGameEntity()
{
}

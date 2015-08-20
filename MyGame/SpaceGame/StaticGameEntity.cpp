#include "StaticGameEntity.h"


StaticGameEntity::StaticGameEntity(CIndieLib* masterInstance, Position3D position, std::string resource, IND_Surface* surface, SpriteCordinateMapper* spriteMapper, float* deltaTime)
	:GameEntity(masterInstance, position, resource, surface, deltaTime)
{
	_spriteMapper = spriteMapper;
}

void StaticGameEntity::draw()
{
	this->getINDIEntity()->setSurface(new IND_Surface(*getSurface()));// GameEntity::getSurface());
	Region regionOfEntity = _spriteMapper->getSpriteRegionByName(getResourcePath());
	this->getINDIEntity()->setRegion(regionOfEntity.getOffSetX(), regionOfEntity.getOffSetY(), regionOfEntity.getWidth(), regionOfEntity.getHeight());
}

void StaticGameEntity::destroy()
{
	if (getINDIEntity() != NULL){
		getMasterInstance()->_entity2dManager->remove(getINDIEntity());
		getINDIEntity()->destroy();
	}
}

void StaticGameEntity::update()
{
	GameEntity::update();
	getINDIEntity()->setAngleXYZ(getINDIEntity()->getAngleX(), getINDIEntity()->getAngleY(), _angleZ);
}

StaticGameEntity::~StaticGameEntity()
{
	
}

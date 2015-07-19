#include "GameEntity.h"

GameEntity::GameEntity(CIndieLib* masterInstance, Position3D position, const char* resourcePath)
	:_masterInstance(masterInstance), _position(position), _resourcePath(resourcePath)
{
	_entity = IND_Entity2d::newEntity2d();
	_masterInstance->_entity2dManager->add(_entity);
}

GameEntity::~GameEntity()
{
	delete _masterInstance;
	delete _resourcePath;

	_entity = 0;

	_resourcePath = 0;
	_masterInstance = 0;
}

void GameEntity::DrawRegion(Region* region)
{
	Draw();
	getINDIEntity()->setRegion(region->getOffSetX(), region->getOffSetY(), region->getWidth(), region->getHeight());
}

Position3D GameEntity::getPosition(){ return _position; }
void GameEntity::setPosition(Position3D position){ _position = position; }

IND_Entity2d* GameEntity::getINDIEntity(){ return _entity; }
CIndieLib* GameEntity::getMasterInstance(){ return _masterInstance; }

const char* GameEntity::getResourcePath(){ return _resourcePath; }

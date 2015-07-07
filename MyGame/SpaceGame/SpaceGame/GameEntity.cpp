#include "GameEntity.h"


GameEntity::GameEntity(CIndieLib* masterInstance, Position3D position, const char* resourcePath)
	:_masterInstance(masterInstance), _position(position), _resourcePath(resourcePath)
{
	_entity = IND_Entity2d::newEntity2d();
	_surface = IND_Surface::newSurface();
	_masterInstance->_surfaceManager->add(_surface, _resourcePath, IND_OPAQUE, IND_32);
	_masterInstance->_entity2dManager->add(_entity);
}

GameEntity::~GameEntity()
{
	delete _masterInstance;
	delete _resourcePath;

	_surface = 0;
	_entity = 0;

	_resourcePath = 0;
	_masterInstance = 0;
}

void GameEntity::Draw()
{	
	_entity->setSurface(_surface);
	_entity->setPosition(_position.getX(), _position.getY(), _position.getZ());
}
void GameEntity::DrawRegion(Region* region)
{
	Draw();
	_entity->setRegion(region->getOffSetX(), region->getOffSetY(), region->getWidth(), region->getHeight());
}

void GameEntity::Destroy(){
	if (_entity != NULL){
		_masterInstance->_entity2dManager->remove(_entity);
		_masterInstance->_surfaceManager->remove(_surface);
		_entity->destroy();
	}
}

Position3D GameEntity::getPosition(){ return _position; }
void GameEntity::setPosition(Position3D position){ _position = position; }

IND_Entity2d* GameEntity::getEntity(){ return _entity; }
IND_Surface* GameEntity::getSurface(){ return _surface; }

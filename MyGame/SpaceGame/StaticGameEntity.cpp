#include "StaticGameEntity.h"


StaticGameEntity::StaticGameEntity(CIndieLib* masterInstance, Position3D position, const char* resourcePath, float* deltaTime)
	:GameEntity(masterInstance, position, resourcePath, deltaTime)
{
	_surface = IND_Surface::newSurface();
}

void StaticGameEntity::draw()
{
	getMasterInstance()->_surfaceManager->add(_surface, getResourcePath(), IND_OPAQUE, IND_32);
	getINDIEntity()->setSurface(_surface);
	getINDIEntity()->setPosition(getPosition().getX(), getPosition().getY(), getPosition().getZ());
}

void StaticGameEntity::destroy()
{
	if (getINDIEntity() != NULL){
		getMasterInstance()->_entity2dManager->remove(getINDIEntity());
		getMasterInstance()->_surfaceManager->remove(_surface);
		getINDIEntity()->destroy();
	}
}

StaticGameEntity::~StaticGameEntity()
{
	_surface = 0;
}

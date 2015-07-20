#include "StaticGameEntity.h"


StaticGameEntity::StaticGameEntity(CIndieLib* masterInstance, Position3D position, const char* resourcePath)
	:GameEntity(masterInstance, position, resourcePath)
{
	_surface = IND_Surface::newSurface();
	getMasterInstance()->_surfaceManager->add(_surface, getResourcePath(), IND_OPAQUE, IND_32);
}

void StaticGameEntity::Draw()
{
	getINDIEntity()->setSurface(_surface);
	getINDIEntity()->setPosition(getPosition().getX(), getPosition().getY(), getPosition().getZ());
}

void StaticGameEntity::Destroy()
{
	if (getINDIEntity() != NULL){
		getMasterInstance()->_entity2dManager->remove(getINDIEntity());
		getMasterInstance()->_surfaceManager->remove(_surface);
		getINDIEntity()->destroy();
	}
}
void StaticGameEntity::Rotate()
{
	
	


}
StaticGameEntity::~StaticGameEntity()
{
	_surface = 0;
}

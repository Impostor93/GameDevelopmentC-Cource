#include "Projectile.h"


Projectile::Projectile(CIndieLib* masterInstance, Position3D position, const char* path) : StaticGameEntity(masterInstance, position, path)
{
}


Projectile::~Projectile()
{
}

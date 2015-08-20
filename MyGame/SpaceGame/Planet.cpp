#include "Planet.h"


Planet::Planet(CIndieLib* masterInstance, Position3D position, const char* path, IND_Surface* surface, SpriteCordinateMapper* spriteMapper, float* deltaTime)
	: StaticGameEntity(masterInstance, position, path, surface, spriteMapper, deltaTime)
{
}


Planet::~Planet()
{
}

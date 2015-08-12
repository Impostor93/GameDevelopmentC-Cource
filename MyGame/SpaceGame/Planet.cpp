#include "Planet.h"


Planet::Planet(CIndieLib* masterInstance, Position3D position, const char* path, float* deltaTime)
	: StaticGameEntity(masterInstance, position, path, deltaTime)
{
}


Planet::~Planet()
{
}

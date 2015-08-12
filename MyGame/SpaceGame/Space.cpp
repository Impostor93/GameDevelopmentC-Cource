#include "Space.h"


Space::Space(CIndieLib* masterInstance, Position3D position, const char* path, float* deltaTime) 
	: StaticGameEntity(masterInstance, position, path, deltaTime)
{
}


Space::~Space()
{

}

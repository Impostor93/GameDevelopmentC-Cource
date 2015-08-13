#pragma once
#include "GameEntity.h"
#include <string>
#include <iostream>
#include <map>
#include "Common.h"

class GameEntityManager
{
public:
	GameEntityManager(CIndieLib* master);
	~GameEntityManager();

	void createAndAddEntity(std::string key, TypeOfGameObject type, Position3D position, const char* resourcePath, float* deltaTime);
	GameEntity* getEntity(std::string key);

	void addEntity(std::string key, GameEntity* entity, TypeOfGameObject type);
	void removeEntity(std::string key);

	void saveEntities(std::string filePath);
	void loadEntityFromJSON(std::string filePath, float* deltaTime);

	void drawEntities();

private:
	map<std::string,GameEntity*> _listOfGameEntities;
	map<std::string, TypeOfGameObject> _listOfGameEntityNamesAndTypes;
	CIndieLib* _indiMasterInstance;
};


#pragma once
#include "GameEntity.h"
#include <string>
#include <iostream>
#include <map>
#include "Common.h"
#include "StaticGameEntity.h"
#include "AnimatedGameEntity.h"
#include "Ship.h"
#include "SpriteCordinateMapper.h"
#include "AnimationMapper.h"

class GameEntityManager
{
public:
	GameEntityManager(CIndieLib* master, SpriteCordinateMapper* mapper, AnimationMapper* animationMapper, const char* resourcePath);
	~GameEntityManager();

	void createAndAddEntity(std::string key, TypeOfGameObject type, Position3D position, const char* resourcePath, float* deltaTime);
	
	GameEntity* getEntity(std::string key);

	void addEntity(std::string key, GameEntity* entity, TypeOfGameObject type);
	void removeEntity(std::string key);

	void saveEntities(std::string filePath);
	void loadEntityFromJSON(std::string filePath, float* deltaTime);

	void drawEntities();
	void update();

	void setRectangleCollisionArea(std::string entityKey, float offsetX, float offsetY, float width, float height);
	void setTriengleCollisionArea(std::string entityKey, Position2D firsVector, Position2D secondVector, Position2D tirthVector);
	void setCircleCollisionArea(std::string entityKey, float offsetX, float offsetY, float radios);
	void setHotSpot(std::string entityKey, float offsetX, float offsetY);
	bool checkForCollision(std::string entityKey, std::string scondEntityKey);
	bool checkForCollision(std::string entityKey, IND_Entity2d* entity, std::string scondEntityKey, IND_Entity2d* secondEntity);

private:
	map<std::string,GameEntity*> _listOfGameEntities;
	map<std::string, TypeOfGameObject> _listOfGameEntityNamesAndTypes;
	CIndieLib* _indiMasterInstance;
	SpriteCordinateMapper* _spriteCordinates;
	AnimationMapper* _animationMapper;

	IND_Surface* _sharedSurface;
};


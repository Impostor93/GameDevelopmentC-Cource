#pragma once
#ifndef GAMEENTITYMANAGER_H
#define GAMEENTITYMANAGER_H

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
#include "SpaceBody.h"
#include "HUD.h"
#include "irrKlang.h"
#include "AudioPlayer.h"

class GameEntityManager
{
public:
	GameEntityManager(CIndieLib* master, SpriteCordinateMapper* mapper, AnimationMapper* animationMapper, const char* resourcePath, ISoundEngine* soundEngine, float* deltaTime);
	~GameEntityManager();

	void createAndAddEntity(std::string key, TypeOfGameObject type, Position3D position, const char* resourcePath);
	
	GameEntity* getEntity(std::string key);
	IND_Surface* getSurface();

	void addEntity(std::string key, GameEntity* entity, TypeOfGameObject type);
	
	TypeOfGameObject getType(std::string key);
	map<std::string, GameEntity*> getEntities();

	void saveEntities(std::string filePath);
	void loadEntityFromJSON(std::string filePath, float* deltaTime);

	void drawEntities();
	void update();

	void setRectangleCollisionArea(std::string entityKey, float offsetX, float offsetY, float width, float height);
	void setTriengleCollisionArea(std::string entityKey, Position2D firsVector, Position2D secondVector, Position2D tirthVector);
	void setCircleCollisionArea(std::string entityKey, float offsetX, float offsetY, float radios);
	void setHotSpot(std::string entityKey, float offsetX, float offsetY);
	bool checkForCollision(std::string entityKey, std::string scondEntityKey);
	bool checkForCollision(std::string entityKey, GameEntity* entity, std::string secondEntityKey, GameEntity* secondEntity);

	void ClearDestoriedSpaceBody();

	void registerEntityForRemove(std::string key);
	void removeRegistratedEntities();

private:
	map<std::string,GameEntity*> _listOfGameEntities;
	map<std::string, TypeOfGameObject> _listOfGameEntityNamesAndTypes;
	vector<std::string> _listOfGameEntitiesToRemove;

	CIndieLib* _indiMasterInstance;
	SpriteCordinateMapper* _spriteCordinates;
	AnimationMapper* _animationMapper;

	IND_Surface* _sharedSurface;
	float* _deltaTime;
	irrklang::ISoundEngine* _soundEngine;

	void removeEntity(std::string key);
};

#endif

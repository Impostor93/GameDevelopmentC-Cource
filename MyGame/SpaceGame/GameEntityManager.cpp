#include "GameEntityManager.h"

GameEntityManager::GameEntityManager(CIndieLib* master, SpriteCordinateMapper* spriteCordinates, AnimationMapper* animationMapper, const char* resourcePath,ISoundEngine* soundEngine, float* deltaTime) :
_indiMasterInstance(master), _spriteCordinates(spriteCordinates), _animationMapper(animationMapper), _soundEngine(soundEngine)
{
	_deltaTime = deltaTime;
	_sharedSurface = IND_Surface::newSurface();
	_indiMasterInstance->_surfaceManager->add(_sharedSurface, resourcePath, IND_OPAQUE, IND_32);
}


GameEntityManager::~GameEntityManager()
{
	_indiMasterInstance->_surfaceManager->remove(_sharedSurface);
	if (_sharedSurface)
		_sharedSurface->destroy();

	_soundEngine->drop();

	_sharedSurface = 0;
}

void GameEntityManager::addEntity(std::string key, GameEntity* entity, TypeOfGameObject type)
{
	_listOfGameEntityNamesAndTypes[key] = type;
	_listOfGameEntities[key] = entity;
}
GameEntity* GameEntityManager::getEntity(std::string key)
{
	if (_listOfGameEntities.count(key) != 0)
		return _listOfGameEntities[key];
	else
		return NULL;
}
IND_Surface* GameEntityManager::getSurface(){ return _sharedSurface; }

map<std::string, GameEntity*> GameEntityManager::getEntities()
{
	return _listOfGameEntities;
}
TypeOfGameObject GameEntityManager::getType(std::string key)
{
	if (_listOfGameEntities.count(key) != 0)
		return _listOfGameEntityNamesAndTypes[key];
	else
		return Null;
}
void GameEntityManager::removeEntity(std::string key)
{
  	GameEntity* entity = getEntity(key);
	if (entity != NULL)
		entity->destroy();
	
	_listOfGameEntities[key] = 0;

	_listOfGameEntities.erase(key);
	_listOfGameEntityNamesAndTypes.erase(key);
}

void GameEntityManager::createAndAddEntity(std::string key, TypeOfGameObject type, Position3D position, const char* resourcePath)
{
	GameEntity* entity = 0;
	if (type == ShipObject)
		entity = new Ship(_indiMasterInstance, position, resourcePath, _sharedSurface, _animationMapper, _deltaTime);
	else if (type == SpaceBodyObject)
		entity = new SpaceBody(_indiMasterInstance, position, resourcePath, _sharedSurface, _animationMapper, _deltaTime);
	else if (type == AnimatedObject)
		entity = new AnimatedGameEntity(_indiMasterInstance, position, resourcePath, _sharedSurface, _animationMapper, _deltaTime);
	else if (type == StaticObject)
		entity = new StaticGameEntity(_indiMasterInstance, position, resourcePath, _sharedSurface, _spriteCordinates, _deltaTime);
	else if (type == HUDObject)
		entity = new HUD(_indiMasterInstance, position, resourcePath, _sharedSurface, _spriteCordinates, _deltaTime);

	addEntity(key, entity, type);
}

void GameEntityManager::saveEntities(std::string filePath)
{

	std::ofstream out(filePath);

	for (std::map<std::string, GameEntity*>::iterator it = _listOfGameEntities.begin(); it != _listOfGameEntities.end(); ++it)
	{
		std::string entity = "{" + it->first + ":" + it->second->serializeEntityState() + ", ";
		entity += " Type:" + Common::IntToString(int(_listOfGameEntityNamesAndTypes[it->first]));
		entity += "}";

		out << (entity + "\n");
	}

	out.close();
}
void GameEntityManager::loadEntityFromJSON(std::string fileName, float* deltaTime)
{
	if (_listOfGameEntities.size() != 0 && _listOfGameEntityNamesAndTypes.size() != 0)
	{
		for (std::map<std::string, GameEntity*>::iterator it = _listOfGameEntities.begin(); it != _listOfGameEntities.end(); ++it)
			it->second->destroy();

		_listOfGameEntityNamesAndTypes.clear();
		_listOfGameEntities.clear();
	}

	// create an input stream
	std::ifstream settingsfile(fileName.c_str());
	// the string variable containing the next line
	std::string line;
	while (std::getline(settingsfile, line))
	{
		std::vector<std::string> elements = Common::splitString(line, ',');
		std::string key = Common::splitString(elements[0], ':')[0];
		key = key.substr(1);

		TypeOfGameObject typeOfObject;
		for (int i = 0; i < elements.size();i++)
		{
			std::vector<std::string> keyValue = Common::splitString(elements[i], ':');
			if (Common::trimString(keyValue[0]) == "Type")
				typeOfObject = (TypeOfGameObject)Common::StringToInt(keyValue[1]);
		}
		
		createAndAddEntity(key, typeOfObject, Position3D(0, 0, 0), "");//When load animations throw exception because empty resource!

		getEntity(key)->deserializeEntity(line);
	}

	settingsfile.close();
}

void GameEntityManager::drawEntities()
{
	for (std::map<std::string, GameEntity*>::iterator it = _listOfGameEntities.begin(); it != _listOfGameEntities.end(); ++it)
		it->second->draw();
}
void GameEntityManager::update()
{
	for (std::map<std::string, GameEntity*>::iterator it = _listOfGameEntities.begin(); it != _listOfGameEntities.end(); ++it)
		it->second->update();

	ClearDestoriedSpaceBody();
}

void GameEntityManager::setRectangleCollisionArea(std::string entityKey, float offsetX, float offsetY, float width, float height)
{
	this->getEntity(entityKey)->getINDIEntity()->setBoundingRectangle(entityKey.c_str(), offsetX, offsetY, width, height);
}
void GameEntityManager::setTriengleCollisionArea(std::string entityKey, Position2D firstVector, Position2D secondVector, Position2D thirdVector)
{
	this->getEntity(entityKey)->getINDIEntity()->setBoundingTriangle(entityKey.c_str(), firstVector.getX(), firstVector.getY()
		, secondVector.getX(), secondVector.getY(), thirdVector.getX(), thirdVector.getY());
}
void GameEntityManager::setCircleCollisionArea(std::string entityKey, float offsetX, float offsetY, float radios)
{
	this->getEntity(entityKey)->getINDIEntity()->setBoundingCircle(entityKey.c_str(), offsetX, offsetY, radios);
}
void GameEntityManager::setHotSpot(std::string entityKey, float offsetX, float offsetY)
{
	this->getEntity(entityKey)->getINDIEntity()->setHotSpot(offsetX, offsetY);
}
bool GameEntityManager::checkForCollision(std::string entityKey, std::string secondEntityKey)
{
	if (!getEntity(entityKey))
		return false;
	if (!getEntity(secondEntityKey))
		return false;

	return _indiMasterInstance->_entity2dManager->isCollision(getEntity(entityKey)->getINDIEntity(), entityKey.c_str(),
		getEntity(secondEntityKey)->getINDIEntity(), secondEntityKey.c_str());
}
bool GameEntityManager::checkForCollision(std::string entityKey, GameEntity* entity, std::string secondEntityKey, GameEntity* secondEntity)
{
	if (!entity || !secondEntity)
		return false;

	if (entity->getINDIEntity() == NULL || secondEntity->getINDIEntity()==NULL)
		return false;

	return _indiMasterInstance->_entity2dManager->isCollision(entity->getINDIEntity(), entityKey.c_str(), secondEntity->getINDIEntity(), secondEntityKey.c_str());
}

void GameEntityManager::ClearDestoriedSpaceBody()
{
	std::vector<std::string> keysOfObjectForDelete;

	for (std::map<std::string, GameEntity*>::iterator it = _listOfGameEntities.begin(); it != _listOfGameEntities.end(); ++it)
	{
		std::string key = it->first;
		if (key != "" && getType(key) == SpaceBodyObject)
		{
			SpaceBody* spaceBody = (SpaceBody*)it->second;
			if (spaceBody->getHealth() <= 0)
			{
				spaceBody->getINDIEntity()->deleteBoundingAreas(key.c_str());
				char* resource = "D:/Vs2012 Project/C++ game development course/ShipGame/GameDevelopmentC-Cource/MyGame/SpaceGame/irrKlang/OriginalIrrKlang/media/explosion.wav";
				if (!_soundEngine->isCurrentlyPlaying(resource))
					_soundEngine->play2D(resource, false);
			}

			if (spaceBody->isBodyDestroyedAndExplosionFinished())
				keysOfObjectForDelete.push_back(key);
		}
	}
	for (int i = 0; i < keysOfObjectForDelete.size(); i++){
		this->removeEntity(keysOfObjectForDelete[i]);
	}
}

void GameEntityManager::registerEntityForRemove(std::string key)
{
	_listOfGameEntitiesToRemove.push_back(key);
}
void GameEntityManager::removeRegistratedEntities()
{
	for (int i = 0; i < _listOfGameEntitiesToRemove.size(); i++) 
	{
		removeEntity(_listOfGameEntitiesToRemove.at(i));
	}

	_listOfGameEntitiesToRemove.clear();
}
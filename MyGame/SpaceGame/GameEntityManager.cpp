#include "GameEntityManager.h"
#include "StaticGameEntity.h"
#include "AnimatedGameEntity.h"
#include "Ship.h"

GameEntityManager::GameEntityManager(CIndieLib* master) :
_indiMasterInstance(master)
{
}


GameEntityManager::~GameEntityManager()
{
	delete _indiMasterInstance;
}

void GameEntityManager::addEntity(std::string key, GameEntity* entity, TypeOfGameObject type)
{
	_listOfGameEntityNamesAndTypes[key] = type;
	_listOfGameEntities[key] = entity;
}
GameEntity* GameEntityManager::getEntity(std::string key)
{
	if (_listOfGameEntities.count(key))
		return _listOfGameEntities[key];
	else
		return NULL;
}
void GameEntityManager::removeEntity(std::string key)
{
	_listOfGameEntities.erase(key);
	_listOfGameEntityNamesAndTypes.erase(key);
}

void GameEntityManager::createAndAddEntity(std::string key, TypeOfGameObject type, Position3D position, const char* resourcePath, float* deltaTime)
{
	GameEntity* entity = 0;
	if (type == StaticObject)
		entity = new StaticGameEntity(_indiMasterInstance, position, resourcePath, deltaTime);
	else if (type == ShipObject)
		entity = new Ship(_indiMasterInstance, position, resourcePath, deltaTime);
	else
		entity = new AnimatedGameEntity(_indiMasterInstance, position, resourcePath, deltaTime);

	_listOfGameEntityNamesAndTypes[key] = type;
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
		_listOfGameEntityNamesAndTypes.clear();
		_listOfGameEntities.clear();
		for (std::map<std::string, GameEntity*>::iterator it = _listOfGameEntities.begin(); it != _listOfGameEntities.end(); ++it)
		{
			it->second->destroy();
			it->second->~GameEntity();
		}
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
		
		createAndAddEntity(key, typeOfObject, Position3D(0, 0, 0), "", deltaTime);

		getEntity(key)->deserializeEntity(line);
	}

	settingsfile.close();
}

void GameEntityManager::drawEntities()
{
	for (std::map<std::string, GameEntity*>::iterator it = _listOfGameEntities.begin(); it != _listOfGameEntities.end(); ++it)
		it->second->draw();
}




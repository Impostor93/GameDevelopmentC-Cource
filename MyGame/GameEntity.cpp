#include "GameEntity.h"


GameEntity::GameEntity(CIndieLib* masterInstance, Position3D position, std::string resourcePath, IND_Surface* surface, float* deltaTime)
	:GameObject(position), _masterInstance(masterInstance), _resourcePath(resourcePath), _surface(surface), _deltaTime(deltaTime)
{
	_entity = IND_Entity2d::newEntity2d();
	_entity->setPosition(_position.getX(), _position.getY(), _position.getZ());

	_masterInstance->_entity2dManager->add(_entity);

	_angleZ = this->getINDIEntity()->getAngleZ();
}

GameEntity::~GameEntity()
{
	delete _masterInstance;
	delete _deltaTime;
	
	if (_entity)
		_entity->destroy();

	//_entity = 0;

	_deltaTime = 0;
	_masterInstance = 0;
}

void GameEntity::destroy()
{
	if (_entity){
		_entity->destroy();
		_masterInstance->_entity2dManager->remove(_entity);
	}
	GameEntity::~GameEntity();
}

void GameEntity::update()
{
	_entity->setPosition(_position.getX(), _position.getY(), _position.getZ());
	this->getINDIEntity()->setAngleXYZ(0, 0, (float)_angleZ);
}

//Setters
void GameEntity::setHotSpot(float x, float y)
{
	float surfaceWidth = _entity->getSurface()->getWidth();
	float surfaceHeight = _entity->getSurface()->getHeight();

	float entityWidth = _entity->getRegionWidth();
	float entityHeight = _entity->getRegionHeight();

	float midleWidth = (entityWidth / surfaceWidth) * x;
	float midleHeight = (entityHeight / surfaceHeight) * y;

	_entity->setHotSpot(midleWidth, midleHeight);
}
void GameEntity::setResourcePath(std::string resource){ _resourcePath = resource; }
void GameEntity::setDemageFactor(int demageFactor){ this->_demageFactor = demageFactor; }
//End Setters

//Getters
IND_Entity2d* GameEntity::getINDIEntity(){ return _entity; }
CIndieLib* GameEntity::getMasterInstance(){ return _masterInstance; }
std::string GameEntity::getResourcePath(){ return _resourcePath; }
IND_Surface* GameEntity::getSurface(){ return _surface; }
int GameEntity::getDemageFactor(){ return _demageFactor; }
//End Getters

//Save/Load
std::string GameEntity::serializeEntityState()
{
	std::string jsonObject = "{";
	jsonObject += _positionKey + ":";
	jsonObject += "{ ";
	jsonObject += "x:" + Common::IntToString(_position.getX()) + ", ";
	jsonObject += "y:" + Common::IntToString(_position.getY()) + ", ";
	jsonObject += "z:" + Common::IntToString(_position.getZ()) + ", ";
	jsonObject += "} , ";
	jsonObject += _angleZKey + ": " + Common::IntToString(_entity->getAngleZ()) + ", ";
	jsonObject += _resourcePathKey + ": " + std::string(_resourcePath);
	jsonObject += " }";

	return jsonObject;
}

void GameEntity::deserializeEntity(std::string jsonObject)
{
	int positionObjectIndex = jsonObject.find(_positionKey) + 2;
	std::size_t firstCloseBreket = jsonObject.find_first_of('}');
	std::string positionObject = jsonObject.substr((positionObjectIndex + _positionKey.length()), (firstCloseBreket - (positionObjectIndex + _positionKey.length())));

	float x = 0, y = 0, z = 0;
	vector<std::string> positionParts = Common::splitString(positionObject, ',');
	for (int i = 0; i < positionParts.size(); i++)
	{
		vector<std::string> parts = Common::splitString(positionParts[i], ':');
		if (Common::trimString(parts[0]) == "x")
			x = (float)Common::StringToInt(parts[1]);
		if (Common::trimString(parts[0]) == "y")
			y = (float)Common::StringToInt(parts[1]);
		if (Common::trimString(parts[0]) == "z")
			z = (float)Common::StringToInt(parts[1]);
	}

	this->setPosition(Position3D(x, y, z));

	vector<std::string> allObjects = Common::splitString(jsonObject, ',');
	for (int i = 0; i < allObjects.size(); i++)
	{
		vector<std::string> parts = Common::splitString(allObjects[i], ':');
		if (Common::trimString(parts[0]) == _angleZKey)
		{
			_angleZ = (float)Common::StringToInt(Common::trimString(parts[1]));
		}
		if (Common::trimString(parts[0]) == _resourcePathKey){
			_tempResourcePath = Common::trimString(parts[1].substr(0, parts[1].find("}") - 1));
			this->_resourcePath = _tempResourcePath.c_str();
		}
	}
}
//End Save/Load

//Game play
void GameEntity::moveForward(float acceleration, bool lockInWindowScreen)
{
	float x = 0.f; x = this->getPosition().getX() + (acceleration * (*_deltaTime)) * (float)sin(this->getINDIEntity()->getAngleZ() / 180.f * PI);
	float y = 0.f; y = this->getPosition().getY() - (acceleration * (*_deltaTime)) * (float)cos(this->getINDIEntity()->getAngleZ() / 180.f * PI);

	if (lockInWindowScreen)
	{
		_width = this->getINDIEntity()->getRegionWidth() / 2 - 18;
		_height = this->getINDIEntity()->getRegionHeight() / 2 - 15;

		if (x + _width > _masterInstance->_window->getWidth()) 
			x = _masterInstance->_window->getWidth() - _width;
		if (x - _width < 0) 
			x = 0 + _width;
		if (y + _height > _masterInstance->_window->getHeight()) 
			y = _masterInstance->_window->getHeight() - _height;
		if (y - _height < 0) 
			y = _height;
	}

	this->setPosition(Position3D(x, y, this->getPosition().getZ()));
}

void GameEntity::moveBackward(float acceleration)
{
	float x = 0.f; x = this->getPosition().getX() - (acceleration * (*_deltaTime)) * (float)sin(this->getINDIEntity()->getAngleZ() / 180.f * PI);
	float y = 0.f; y = this->getPosition().getY() + (acceleration * (*_deltaTime)) * (float)cos(this->getINDIEntity()->getAngleZ() / 180.f * PI);

	this->setPosition(Position3D(x, y, this->getPosition().getZ()));
}

void GameEntity::rotateLeft(float rotationSpeed)
{
	_angleZ = this->getINDIEntity()->getAngleZ() - rotationSpeed * (*_deltaTime);
}
void GameEntity::rotateRight(float rotationSpeed)
{
	_angleZ = this->getINDIEntity()->getAngleZ() + rotationSpeed * (*_deltaTime);
}
//End Game play

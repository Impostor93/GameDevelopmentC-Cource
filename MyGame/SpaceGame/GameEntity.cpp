#include "GameEntity.h"


GameEntity::GameEntity(CIndieLib* masterInstance, Position3D position, const char* resourcePath, float* deltaTime)
	:_masterInstance(masterInstance), _position(position), _resourcePath(resourcePath), _deltaTime(deltaTime)
{
	_entity = IND_Entity2d::newEntity2d();
	_masterInstance->_entity2dManager->add(_entity);

	_width = this->getINDIEntity()->getRegionWidth() / 2;
	_height = this->getINDIEntity()->getRegionHeight() / 2;
}

GameEntity::~GameEntity()
{
	delete _masterInstance;
	delete _resourcePath;
	delete _deltaTime;
	
	//if (_entity)
	//	_entity->destroy();

	_entity = 0;

	_deltaTime = 0;
	_resourcePath = 0;
	_masterInstance = 0;
}

void GameEntity::drawRegion(Region* region)
{
	draw();
	getINDIEntity()->setRegion(region->getOffSetX(), region->getOffSetY(), region->getWidth(), region->getHeight());
}

Position3D GameEntity::getPosition(){ return _position; }
void GameEntity::setPosition(Position3D position)
{ 
	_position = position; 
	_entity->setPosition(position.getX(), position.getY(), position.getZ());
}

IND_Entity2d* GameEntity::getINDIEntity(){ return _entity; }
CIndieLib* GameEntity::getMasterInstance(){ return _masterInstance; }

const char* GameEntity::getResourcePath(){ return _resourcePath; }

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

	int x = 0, y = 0, z = 0;
	vector<std::string> positionParts = Common::splitString(positionObject, ',');
	for (int i = 0; i < positionParts.size();i++)
	{
		vector<std::string> parts = Common::splitString(positionParts[i], ':');
		if (Common::trimString(parts[0]) == "x")
			x = Common::StringToInt(parts[1]);
		if (Common::trimString(parts[0]) == "y")
			y = Common::StringToInt(parts[1]);
		if (Common::trimString(parts[0]) == "z")
			z = Common::StringToInt(parts[1]);
	}

	this->setPosition(Position3D(x,y,z));

	vector<std::string> allObjects = Common::splitString(jsonObject, ',');
	for (int i = 0; i < allObjects.size(); i++)
	{
		vector<std::string> parts = Common::splitString(allObjects[i], ':');
		if (Common::trimString(parts[0]) == _angleZKey)
		{
			_entity->setAngleXYZ(0, 0, Common::StringToInt(Common::trimString(parts[1])));
		}
		if (Common::trimString(parts[0]) == _resourcePathKey){
			_tempResourcePath = Common::trimString(parts[1].substr(0, parts[1].find("}")-1));
			this->_resourcePath = _tempResourcePath.c_str();
		}
	}
}

void GameEntity::destroy()
{
	if (_entity){
		_entity->destroy();
		_masterInstance->_entity2dManager->remove(_entity);
	}
}

void GameEntity::moveForward(float acceleration, bool lockInWindowScreen)
{
	float x = 0.f; x = this->getPosition().getX() + (acceleration * (*_deltaTime)) * (float)sin(this->getINDIEntity()->getAngleZ() / 180.f * PI);
	float y = 0.f; y = this->getPosition().getY() - (acceleration * (*_deltaTime)) * (float)cos(this->getINDIEntity()->getAngleZ() / 180.f * PI);

	if (lockInWindowScreen)
	{
		if (x + _width > _masterInstance->_window->getWidth()) 
			x = _masterInstance->_window->getWidth();
		if (x - _width < 0) 
			x = 0;
		if (y + _height > _masterInstance->_window->getHeight()) 
			y = _masterInstance->_window->getHeight();
		if (y - _height < 0) 
			y = 0;
	}

	this->setPosition(Position3D(x, y, this->getPosition().getZ()));
}

void GameEntity::moveBackward(float acceleration)
{
	float x = 0.f; x = this->getPosition().getX() - (acceleration * (*_deltaTime)) * (float)sin(this->getINDIEntity()->getAngleZ() / 180.f * PI);
	float y = 0.f; y = this->getPosition().getY() + (acceleration * (*_deltaTime)) * (float)cos(this->getINDIEntity()->getAngleZ() / 180.f * PI);

	//float x = this->getPosition().getX() - acceleration * (*_deltaTime) - sin(this->getINDIEntity()->getAngleZ()*3.14 / 180.f);
	//float y = this->getPosition().getY() - acceleration * (*_deltaTime) + cos(this->getINDIEntity()->getAngleZ()*3.14 / 180.f);

	this->setPosition(Position3D(x, y, this->getPosition().getZ()));
}

void GameEntity::rotateLeft(float rotationSpeed)
{
	float mAngle = this->getINDIEntity()->getAngleZ() - rotationSpeed * (*_deltaTime);
	this->getINDIEntity()->setAngleXYZ(0, 0, (float)mAngle);
}
void GameEntity::rotateRight(float rotationSpeed)
{
	float mAngle = this->getINDIEntity()->getAngleZ() + rotationSpeed * (*_deltaTime);
	this->getINDIEntity()->setAngleXYZ(0, 0, (float)mAngle);
}


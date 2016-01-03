#pragma once

#include <iostream>
#include <vector>
#include <sstream>

class Common
{
public:
	Common();
	~Common();

	static int StringToInt(std::string strValue);

	static std::string IntToString(int a);

	static std::string trimString(std::string value);
	static std::vector<std::string> splitString(std::string stringForSearching, char separator);

	//Constants

};
enum TypeOfGameObject
{
	Null,
	ShipObject,
	StaticObject,
	AnimatedObject,
	SpaceBodyObject,
	HUDObject
};
enum ShipState
{
	Accelerate,
	Deaccelerate,
	ReflectBack,
	ReflectFront,
	Soar,
	Peace,
	AccelerateBack
};
enum ShipRotationState
{
	Left,
	Right,
	None
};


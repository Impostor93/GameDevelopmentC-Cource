#pragma once
#include "Position3D.h"

class GameObject
{
public:
	GameObject(Position3D position);
	~GameObject();

	Position3D getPosition();
	void setPosition(Position3D position);

	void virtual draw() = 0;
	void virtual destroy() = 0;

protected:
	Position3D _position;
};

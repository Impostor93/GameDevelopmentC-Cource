#include "GameObject.h"


GameObject::GameObject(Position3D position) :
	_position(position)
{
}

void GameObject::setPosition(Position3D position) { _position = position; }
Position3D GameObject::getPosition() { return _position; }

GameObject::~GameObject()
{
}

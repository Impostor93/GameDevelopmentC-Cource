#include "Object.h"
#include <iostream>
using namespace std;

GameObject::GameObject(Position position)
{
	_position = position;
}

void GameObject::Destroy()
{
	system("cls");
}
Position GameObject::getPosition()
{
	return _position;
}
void GameObject::setPosition(Position position)
{
	_position = position;
}


GameObject::~GameObject()
{

}
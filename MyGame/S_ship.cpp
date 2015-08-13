#include<iostream>
#include "ship.h";
using namespace std;

void Ship::setPosition(double &X, double &Y)
{
	this->X = X;
	this->Y = Y;
}

void Ship::destroy()
{
	system("cls");
	cout << "Destroyed at: " << endl;
	this->currentPosition();
}

void Ship::visualise()
{
	cout << "  S H I P\n" << endl;
	cout << " S  H  I  P\n" << endl;
	cout << "  S H I P\n" << endl;
}

bool Ship::isMoving()
{
	return this->_isMoving;
}


void Ship::currentPosition()
{
	cout << "X= " << this->X << "Y= " << this->Y << endl;
}

Ship::Ship(double X,double Y)
{
	this->X = X;
	this->Y = Y;
}

Ship::~Ship()
{

}


#ifndef SHIP_H
#define SHIP_H
#include<iostream>
using namespace std;

class Ship
{
	public:
		Ship(double x, double y);
		~Ship(); 
	
	void setPosition(double &X, double &Y);
	void destroy();
	void visualise();
	bool isMoving();
	void currentPosition();

	private:
		bool _isMoving = false;
		double X = 0.0;
		double Y = 0.0;

};
#endif
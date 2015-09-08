#pragma once

#ifndef POSITION2D_H
#define POSITION2D_H

class Position2D
{
public:
	Position2D();
	Position2D(float x, float y);

	~Position2D();

	float getX();
	float getY();

	
private:
	float _x;
	float _y;

protected:
	void setX(float x);
	void setY(float y);
};

#endif
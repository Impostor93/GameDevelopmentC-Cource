#pragma once
class Position2D
{
public:
	Position2D();
	Position2D(int x, int y);

	~Position2D();

	int getX();
	int getY();

	void setX(int x);
	void setY(int y);
private:	
	int _x;
	int _y;
};


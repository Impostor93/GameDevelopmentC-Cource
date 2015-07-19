#pragma once
class Region
{
public:
	Region();
	Region(int offsetY,int offsetX, int width, int height);
	~Region();

	//Getters
	int getOffSetY();
	int getOffSetX();
	int getWidth();
	int getHeight();

	//Setters
	void setOffSetY(int offsetY);
	void setOffSetX(int offsetX);
	void setWidth(int width);
	void setHeight(int height);

private:
	int _offSetY;
	int _offSetX;
	int _width;
	int _height;
};


#pragma once
class Region
{
public:
	Region();
	Region(float offsetY, float offsetX, float width, float height);
	~Region();

	//Getters
	float getOffSetY();
	float getOffSetX();
	float getWidth();
	float getHeight();

	//Setters
	void setOffSetY(float offsetY);
	void setOffSetX(float offsetX);
	void setWidth(float width);
	void setHeight(float height);

private:
	float _offSetY;
	float _offSetX;
	float _width;
	float _height;
};


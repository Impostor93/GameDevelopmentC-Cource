#include "Region.h"


Region::Region() : 
_offSetX(0), _offSetY(0), _width(0), _height(0)
{
}

Region::Region(float offsetY, float offsetX, float width, float height) :
_offSetX(offsetX), _offSetY(offsetY), _width(width), _height(height)
{
}


Region::~Region()
{
}

float Region::getOffSetY(){ return _offSetY; }
float Region::getOffSetX(){ return _offSetX; }
float Region::getWidth(){ return _width; }
float Region::getHeight(){ return _height; }

//Setters
void Region::setOffSetY(float offsetY) { _offSetY = offsetY; }
void Region::setOffSetX(float offsetX){ _offSetX = offsetX; }
void Region::setWidth(float width){ _width = width; }
void Region::setHeight(float height){ _height = height; }
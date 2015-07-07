#include "Region.h"


Region::Region() : 
_offSetX(0), _offSetY(0), _width(0), _height(0)
{
}

Region::Region(int offsetY, int offsetX, int width, int height):
_offSetX(offsetX), _offSetY(offsetY), _width(width), _height(height)
{
}


Region::~Region()
{
}

int Region::getOffSetY(){ return _offSetY; }
int Region::getOffSetX(){ return _offSetX; }
int Region::getWidth(){ return _width; }
int Region::getHeight(){ return _height; }

//Setters
void Region::setOffSetY(int offsetY) { _offSetY = offsetY; }
void Region::setOffSetX(int offsetX){ _offSetX = offsetX; }
void Region::setWidth(int width){ _width = width; }
void Region::setHeight(int height){ _height = height; }
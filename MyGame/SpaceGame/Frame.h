#pragma once
#include "Region.h"

class Frame
{
private:
	Region _region;
	int _time = 0;

public:
	Frame(Region region, int time);
	~Frame();

	Region getRegionOfFrame();
	int getTime();
};


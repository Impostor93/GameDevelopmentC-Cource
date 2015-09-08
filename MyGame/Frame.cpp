#include "Frame.h"

Frame::Frame(Region region, int time):
_region(region), _time(time)
{

}

Region Frame::getRegionOfFrame(){ return _region; }
int Frame::getTime(){ return _time; }

Frame::~Frame()
{
}

#include "AnimationMapper.h"


AnimationMapper::AnimationMapper(SpriteCordinateMapper* spriteCordinateMapper):
_spriteCordinateMapper(spriteCordinateMapper)
{

}

void AnimationMapper::loadAnimationeMap(std::string fileName)
{
	std::ifstream settingsfile(fileName.c_str());
	// the string variable containing the next line
	std::string line;

	std::vector<Frame> frames;
	std::string key = "";
	bool isFirstAnimation = true;

	while (std::getline(settingsfile, line))
	{
		
		if (line.find("AnimationName") != std::string::npos)
		{
			if (!isFirstAnimation)
			{
				_animationFrames.insert(std::pair<std::string, std::vector<Frame>>(key, frames));
				frames.clear();
			}

			std::vector<std::string> headers = Common::splitString(line, '=');
			key = headers[1];

			isFirstAnimation = false;
		}
		else
		{
			std::vector<std::string> values = Common::splitString(line, ',');
			Region region = _spriteCordinateMapper->getSpriteRegionByName(Common::trimString(values[0]));
			int time = Common::StringToInt(values[1]);

			frames.push_back(Frame(region, time));
		}
	}

	_animationFrames.insert(std::pair<std::string, std::vector<Frame>>(key, frames));

	settingsfile.close();
}
std::vector<Frame> AnimationMapper::getAnimationByName(std::string name)
{
	return _animationFrames.at(name);
}

SpriteCordinateMapper* AnimationMapper::getSpriteCordinateMapper(){ return _spriteCordinateMapper; }

AnimationMapper::~AnimationMapper()
{
	delete _spriteCordinateMapper;
	_spriteCordinateMapper = 0;
}

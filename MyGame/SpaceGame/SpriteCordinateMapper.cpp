#include "SpriteCordinateMapper.h"


SpriteCordinateMapper::SpriteCordinateMapper()
{
}


SpriteCordinateMapper::~SpriteCordinateMapper()
{
}

void SpriteCordinateMapper::loadSpriteMap(std::string fileName)
{
	// create an input stream
	std::ifstream settingsfile(fileName.c_str());
	// the string variable containing the next line
	std::string line;
	bool isHeaderLine = true;
	std::string headersLine[5];

	while (std::getline(settingsfile, line))
	{
		if (isHeaderLine)
		{
			std::vector<std::string> headers = Common::splitString(line, ',');
			headersLine[0] = Common::trimString(headers[0]);
			headersLine[1] = Common::trimString(headers[1]);
			headersLine[2] = Common::trimString(headers[2]);
			headersLine[3] = Common::trimString(headers[3]);
			headersLine[4] = Common::trimString(headers[4]);

			isHeaderLine = false;
		}
		else
		{
			std::vector<std::string> values = Common::splitString(line, ',');
			int offSetX = Common::StringToInt(values[1]);
			int offSetY = Common::StringToInt(values[2]);
			int width = Common::StringToInt(values[3]);
			int height = Common::StringToInt(values[4]);
			
			std::string key = Common::trimString(values[0]);

			if (!_spriteRegions.count(key))
				_spriteRegions.insert(std::pair<std::string, Region>(key, Region(offSetY, offSetX, width, height)));
			else
			{
				std::string message = "Duplicate key:" + key;
				throw new std::exception(message.c_str());
			}
		}
	}

	settingsfile.close();
}

Region SpriteCordinateMapper::getSpriteRegionByName(std::string name)
{
	return _spriteRegions.at(name);
}

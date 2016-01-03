#include "ConfigurationReader.h"


ConfigurationReader::ConfigurationReader(const char* fileName)
{
	read(fileName);
}

void ConfigurationReader::read(const char* fileName)
{
	// create an input stream
	std::ifstream settingsfile(fileName);
	// the string variable containing the next line
	std::string line;
	while (std::getline(settingsfile, line))
	{
		std::vector<std::string> elements = this->splitString(line, '=');
		_settings[elements[0]] = elements[1];
	}

	settingsfile.close();

}
std::vector<std::string> ConfigurationReader::splitString(std::string stringForSearching, char separator)
{
	std::vector<std::string> strings = std::vector<std::string>();
	std::string part = "";
	for (int i = 0; i < stringForSearching.length(); i++)
	{
		if (stringForSearching[i] == separator || i == stringForSearching.length() - 1)
		{
			if (i == stringForSearching.length() - 1)
				part += stringForSearching[i];

			strings.push_back(part);
			part = "";
		}
		else
		{
			part += stringForSearching[i];
		}
	}

	return strings;
}

std::string ConfigurationReader::getSetting(std::string key)
{
	return _settings.at(key);
}

ConfigurationReader::~ConfigurationReader()
{
}

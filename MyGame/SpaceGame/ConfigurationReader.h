#pragma once
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <fstream>

using namespace std;

class ConfigurationReader
{
public:
	ConfigurationReader(const char* fileName);
	~ConfigurationReader();

	std::string getSetting(std::string key);

private:
	void read(const char* fileName);
	const char* _fileName;
	map<std::string, std::string> _settings;

	std::vector<std::string> splitString(std::string stringForSearching, char separator);
};


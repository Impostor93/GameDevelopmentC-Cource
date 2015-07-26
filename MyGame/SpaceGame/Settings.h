#ifndef SETTINGS_
#define SETTINGS_

#include "CIndieLib.h"
#include "IND_Surface.h"
#include "IND_Entity2d.h"
#include <string>
#include <fstream>
#include <map>
using namespace std;


class Settings
{
public:
	Settings(map<string, string> Mysettings);
	~Settings();

	void  trimspaces(string& value);
	void  loadSettings(const string& filename);

private:
	map<string, string> settings_;

};

#endif
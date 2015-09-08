#include "Settings.h"

Settings::Settings(map<string, string> Mysettings)
{
	settings_.insert(Mysettings.begin(), Mysettings.end());
}
Settings::~Settings()
{

}
void Settings::trimspaces(string& value)
{
	char const* delims = " \t\r\n";					// set the type of characters that should be removed from the string
	size_t pos = value.find_first_not_of(delims);	// find the position of the first character that is not a delimeter 
	value.erase(0, pos);							// remove all characters upto the position specified
	pos = value.find_last_not_of(delims);			// find the last non-delimeter in the remaining string
	value.erase(pos + 1);							// remove all characters after the position specified
}

void  Settings::loadSettings(const string& filename)
{
	settings_.clear();								// first clear the existing settings
	ifstream settingsfile(filename.c_str());		// create an input stream
	string line;									// the string variable containing the next line
													
	while (std::getline(settingsfile, line))		// while the file has not reached its end...
	{
		if (line.c_str()[0] != '#')						// ... check if the line is not a comment line ...
		{				
		size_t pos = line.find_first_of("=");				// ... and find the '=' sign.
		string param, value;								
		param = line.substr(0, pos);  trimspaces(param);	// get the first part (property/param) of the string
		value = line.substr(pos + 1);  trimspaces(value);	// get the last part (value) of the string
		settings_[param] = value;							// store the param/value pair in the settings_ variable
		}
	}
	settingsfile.close();							// finally, close the input stream
}

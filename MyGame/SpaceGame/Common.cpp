#include "Common.h"

int Common::StringToInt(std::string strValue)
{
	return atoi(trimString(strValue).c_str());
}
std::string Common::IntToString(int number)
{
	return static_cast<std::ostringstream*>(&(std::ostringstream() << number))->str();
}

std::string Common::trimString(std::string value)
{
	char const* delims = " \t\r\n";
	size_t pos = value.find_first_not_of(delims);
	value.erase(0, pos);
	pos = value.find_last_not_of(delims);
	return value.erase(pos + 1);
}
std::vector<std::string> Common::splitString(std::string stringForSearching, char separator)
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

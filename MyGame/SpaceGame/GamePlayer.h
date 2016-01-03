#pragma once
#include <iostream>

class GamePlayer
{
public:
	GamePlayer(std::string authToken, std::string instanceKey, std::string credits);
	~GamePlayer();

	std::string AuthToken;
	std::string InstanceKey;
	std::string Credits;
};


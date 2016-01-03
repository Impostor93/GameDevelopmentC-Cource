#include "GamePlayer.h"


GamePlayer::GamePlayer(std::string authToken, std::string instanceKey, std::string credits)
{
	AuthToken = authToken;
	InstanceKey = instanceKey;
	Credits = credits;
}


GamePlayer::~GamePlayer()
{
}

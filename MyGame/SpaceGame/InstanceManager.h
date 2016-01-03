#pragma once
#pragma comment(lib, "IPHLPAPI.lib")
#pragma comment(lib,"ws2_32.lib")

#define WIN32_LEAN_AND_MEAN        
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <windows.h>      
#include <winsock2.h>
#include <intrin.h>       
#include <iphlpapi.h>  
#include <iostream>
#include <stdio.h>
#include <sstream>
#include "GamePlayer.h"

class InstanceManager
{
public:
	InstanceManager();
	~InstanceManager();

	static std::string getMachineName();

	bool registratGame(std::string token, std::string computerKey);

	GamePlayer* getPlayer(std::string token, std::string computerKey);

private:
	int sendRequestToRegistrate(std::string request, std::string* response);
	std::string createRegistrationRequest(std::string token, std::string computerKey);
	std::string createRequest(std::string method, std::string body);
	std::string getWSDLTagContent(std::string responseText, std::string tagName);

	std::string intToString(int number);

	const int port = 1452;
	const std::string serviceHost = "localhost";
};


#include "InstanceManager.h"


InstanceManager::InstanceManager()
{

}
InstanceManager::~InstanceManager()
{

}

std::string InstanceManager::getMachineName()
{
	char data[4096];
	ZeroMemory(data, 4096);
	unsigned long  len = 4000;
	PIP_ADAPTER_INFO pinfo = (PIP_ADAPTER_INFO)data;
	char sbuf[20];
	std::string sret;

	DWORD ret = GetAdaptersInfo(pinfo, &len);
	if (ret != ERROR_SUCCESS)
		return std::string("**ERROR**");

	for (int k = 0; k < 5; k++) {
		sprintf_s(sbuf, "%02X-", pinfo->Address[k]);
		sret += sbuf;
	}
	sprintf_s(sbuf, "%02X", pinfo->Address[5]);
	sret += sbuf;

	return sret;
}

bool InstanceManager::registratGame(std::string token, std::string computerKey)
{
	std::string request = createRegistrationRequest(token, computerKey);
	std::string response;
	int isRequestSuccess = sendRequestToRegistrate(request, &response);

	std::string isValid = getWSDLTagContent(response, "RegistrateGameInstanceIfIsNotResult");
	return (isValid == "true");
}

GamePlayer* InstanceManager::getPlayer(std::string token, std::string computerKey)
{
	std::string body = "";

	body += "<soapenv:Envelope xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:tem=\"http://tempuri.org/\">\r\n";
	body += "   <soapenv:Header/>\r\n";
	body += "   <soapenv:Body>\r\n";
	body += "      <tem:GetPlayerInstance>\r\n";
	body += "         <tem:authToken>" + token + "</tem:authToken>\r\n";
	body += "         <tem:playerAuthToken>" + computerKey + "</tem:playerAuthToken>\r\n";
	body += "       </tem:GetPlayerInstance>\r\n";
	body += "   </soapenv:Body>\r\n";
	body += "</soapenv:Envelope>\r\n ";

	std::string response;
	sendRequestToRegistrate(createRequest("GetPlayerInstance", body), &response);

	std::string authToken = getWSDLTagContent(response, "LicenseKey");
	std::string instanceKey = getWSDLTagContent(response, "MachineKey");
	std::string credits = getWSDLTagContent(response, "Credits");

	return new GamePlayer(authToken, instanceKey, credits);
}

int InstanceManager::sendRequestToRegistrate(std::string request, std::string* response)
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		return -1;
	}
	SOCKET Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct hostent *host;
	host = gethostbyname(serviceHost.c_str());
	SOCKADDR_IN SockAddr;
	SockAddr.sin_port = htons(port);
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);
	if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0){
		return -1;
	}

	send(Socket, request.c_str(), strlen(request.c_str()), 0);
	char buffer[10000];
	int nDataLength;
	while ((nDataLength = recv(Socket, buffer, 10000, 0)) > 0){
		int i = 0;
		while (buffer[i] >= 32 || buffer[i] == '\n' || buffer[i] == '\r') {
			response += buffer[i];
			i += 1;
		}
	}
	closesocket(Socket);
	WSACleanup();

	return 0;
}
std::string InstanceManager::createRegistrationRequest(std::string token, std::string computerKey)
{
	std::string body = "";

	body += "<soapenv:Envelope xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" xmlns:tem=\"http://tempuri.org/\">\r\n";
	body += "   <soapenv:Header/>\r\n";
	body += "   <soapenv:Body>\r\n";
	body += "      <tem:RegistrateGameInstance>\r\n";
	body += "         <tem:authToken>" + token + "</tem:authToken>\r\n";
	body += "         <tem:instanceKey>" + computerKey + "</tem:instanceKey>\r\n";
	body += "       </tem:RegistrateGameInstance>\r\n";
	body += "   </soapenv:Body>\r\n";
	body += "</soapenv:Envelope>\r\n ";

	return createRequest("RegistrateGameInstance", body);
}
std::string InstanceManager::createRequest(std::string method, std::string body)
{
	std::string headers = "";
	headers += "POST /GameServices.svc HTTP/1.1 \r\n";
	headers += "Accept-Encoding: gzip,deflate\r\n";
	headers += "Content-Type: text/xml;charset=UTF-8\r\n";
	headers += "SOAPAction: \"http://tempuri.org/IGameService/" + method + "\"\r\n";

	std::string hostHeader = "Host: " + serviceHost + ":" + intToString(port) + "\r\n\n";
	std::string contentLengthHeaders = "Content-Length: " + intToString(headers.length() + body.length() + hostHeader.length() + 23) + "\r\n";

	headers += contentLengthHeaders;
	headers += hostHeader;

	return (headers + body);
}

std::string InstanceManager::getWSDLTagContent(std::string responseText, std::string tagName)
{
	return responseText.substr(responseText.find("<" + tagName + ">"), responseText.find("</" + tagName + ">"));
}

std::string InstanceManager::intToString(int number)
{
	return static_cast<std::ostringstream*>(&(std::ostringstream() << number))->str();
}


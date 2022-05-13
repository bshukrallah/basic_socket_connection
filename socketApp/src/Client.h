#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>

class chatClient {

public:

	chatClient();
	~chatClient() { WSACleanup(); };

	int createSocket();
	int serverConnect(std::string ipInput, int port);

	void chatStream();

	SOCKET getSocket();

private:

	SOCKET clientSocket;
	WSADATA wsaData;
	int wsaerr;

};
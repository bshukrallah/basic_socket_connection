#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iostream>


class chatServer {
public:
	chatServer();
	~chatServer() { WSACleanup(); };
	int createSocket();
	int bindSocket(int port);
	int acceptConnections();

	void listeningService();
	void chatStream();


private:

	SOCKET serverSocket, acceptSocket;
	WSADATA wsaData;

	int wsaerr;

};
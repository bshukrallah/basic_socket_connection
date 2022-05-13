#include "Server.h"

chatServer::chatServer() {
	std::cout << "\n=======================\n";
	std::cout << "======= SERVER ========\n";
	std::cout << "=======================\n\n";
	createSocket();
};

int chatServer::createSocket() 
{
	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0) {
		std::cout << "[!] Winsock DLL not found" << std::endl;
		return 0;
	}
	else {
		std::cout << "[+] Status: " << wsaData.szSystemStatus << std::endl;
	}

	serverSocket = INVALID_SOCKET;
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET) {
		std::cout << "[!] Error at socket(): " << WSAGetLastError() << std::endl;
		WSACleanup();
		return 0;
	}
	else {
		std::cout << "[+] Socket() is OK!" << std::endl;
	}
};

int chatServer::bindSocket(int port)
{
	sockaddr_in service;
	service.sin_family = AF_INET;
	InetPton(AF_INET, L"127.0.0.1", &service.sin_addr.s_addr);
	service.sin_port = htons(port);
	if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
		std::cout << "Bind() failed: " << WSAGetLastError() << std::endl;
		closesocket(serverSocket);
		WSACleanup();
		return 0;
	}
	else {
		std::cout << "[+] Socket bind() is OK!" << std::endl;
	}

}

void chatServer::listeningService(){

	if (listen(serverSocket, 1) == SOCKET_ERROR) {
		std::cout << "[!] listen(): Error listening on socket " << WSAGetLastError() << std::endl;
	}
	else {
		std::cout << "Ready for Connections..." << std::endl;
	}
	acceptConnections();
};

int chatServer::acceptConnections() 
{
	acceptSocket = accept(serverSocket, NULL, NULL);
	if (acceptSocket == INVALID_SOCKET) {
		std::cout << "[!] Invalid Socket -- Connection failed: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return -1;
	}
	std::cout << "**Connection Accepted**" << std::endl;
};

void chatServer::chatStream() {
	int byteCount;
	char sendBuffer[200];
	std::cout << "Server-> ";
	std::cin.getline(sendBuffer, 200);
	byteCount = send(acceptSocket, sendBuffer, 200, 0);
}

SOCKET chatServer::getSocket() {
	return acceptSocket;
}
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

int main() {

	std::cout << "\n=======================\n";
	std::cout << "======= SERVER ========\n";
	std::cout << "=======================\n\n";


	//create socket
	
	SOCKET serverSocket, acceptSocket;

	int port = 55555;

	WSADATA wsaData;
	int wsaerr;

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

	//bind socket

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
	std::cout << "\n==Set Up Listening==\n";
	if (listen(serverSocket, 1) == SOCKET_ERROR) {
		std::cout << "[!] listen(): Error listening on socket " << WSAGetLastError() << std::endl;
	}
	else {
		std::cout << "[+] listen() is OK! Waiting for connections..." << std::endl;
	}

	//accept connections

	acceptSocket = accept(serverSocket, NULL, NULL);
	if (acceptSocket == INVALID_SOCKET) {
		std::cout << "[!] Invalid Socket -- Connection failed: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return -1;
	}
	std::cout << "**Connection Accepted**" << std::endl;


	while (true) {
		char buffer[200];
		char sendBuffer[200];

		int byteCount = recv(acceptSocket, buffer, 200, 0);

		if (byteCount > 0) {
			std::cout << "Client-> " << buffer << std::endl;
		}
		else WSACleanup();

		std::cout << "Server-> ";
		std::cin.getline(sendBuffer, 200);

		byteCount = send(acceptSocket, sendBuffer, 200, 0);
	}


	system("pause");
	WSACleanup();
}
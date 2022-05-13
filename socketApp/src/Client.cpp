#include "Client.h"

chatClient::chatClient() {
	std::cout << "\n=======================\n";
	std::cout << "======= CLIENT ========\n";
	std::cout << "=======================\n\n";
};

int chatClient::createSocket() 
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

	clientSocket = INVALID_SOCKET;
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET) {
		std::cout << "[!] Error at socket(): " << WSAGetLastError() << std::endl;
		WSACleanup();
		return 0;
	}
	else {
		std::cout << "[+] Socket() is OK!" << std::endl;
	}
};

int chatClient::serverConnect(std::string ipInput, int port) 
{
	std::wstring ipConvert = std::wstring(ipInput.begin(), ipInput.end());

	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	InetPton(AF_INET, ipConvert.c_str(), &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(port);
	if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
		std::cout << "[!] Connection failed: " << WSAGetLastError() << std::endl;
		std::cout << "Make sure server is running\n\n" << std::endl;
		closesocket(clientSocket);
		WSACleanup();
		system("pause");
		return 0;
	}
	else {
		std::cout << "[+] Client: connection to server is OK!" << std::endl;
		std::cout << "**Can now send and recieve data!**\n\n" << std::endl;
	}
};

void chatClient::chatStream() 
{
	char buffer[200];
	std::cout << "Client-> ";
	std::cin.getline(buffer, 200);

	int byteCount = send(clientSocket, buffer, 200, 0);

	byteCount = recv(clientSocket, buffer, 200, 0);
	if (byteCount > 0) {
		std::cout << "Server-> " << buffer << std::endl;
	}
	else WSACleanup();
};

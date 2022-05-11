#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

int main() {

	std::cout << "\n=======================\n";
	std::cout << "======= CLIENT ========\n";
	std::cout << "=======================\n\n";

	SOCKET clientSocket;
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

	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	InetPton(AF_INET, L"127.0.0.1", &clientService.sin_addr.s_addr);
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

	system("pause");
	WSACleanup();
	return 0;
}
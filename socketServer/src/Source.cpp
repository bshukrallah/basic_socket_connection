#include <iostream>
#include <thread>
#include "Server.h"

//server

SOCKET serverSocket;

void listenMgr() {
	using namespace std::literals::chrono_literals;

	while (true) {
		int byteCount;
		char rcvBuffer[200];
		byteCount = recv(serverSocket, rcvBuffer, 200, 0);
		if (byteCount > 0) {
			std::cout << "\nClient-> " << rcvBuffer << "\nServer-> ";
		}
		else WSACleanup();

		std::this_thread::sleep_for(100ms);
	}
}

int main() {
	std::unique_ptr<chatServer> chatServ = std::make_unique<chatServer>();

	system("Color 0A");

	int port = 55555;
	chatServ->bindSocket(port);
	chatServ->listeningService();

	serverSocket = chatServ->getSocket();

	std::thread listener(listenMgr);

	while (true) {
		chatServ->chatStream();
	}

	system("pause");
}
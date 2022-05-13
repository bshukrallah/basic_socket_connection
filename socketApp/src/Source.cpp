#include <iostream>
#include <thread>
#include <iomanip>
#include <ctime>
#include <sstream>
#include "Client.h"

//client

SOCKET clientSocket;

void listenMgr() {
	using namespace std::literals::chrono_literals;

	while (true) {
		int byteCount;
		char rcvBuffer[200];
		byteCount = recv(clientSocket, rcvBuffer, 200, 0);
		if (byteCount > 0) {
			std::cout << "\nServer-> " << rcvBuffer << "\nClient-> ";
		}
		else WSACleanup();

		std::this_thread::sleep_for(100ms);
	}
}

int main() {
	std::unique_ptr<chatClient> clientChat = std::make_unique<chatClient>();

	system("Color 0A");

	clientChat->createSocket();

	int port = 55555;
	std::string ipInput = "127.0.0.1";

	clientChat->serverConnect(ipInput, port);

	clientSocket = clientChat->getSocket();

	std::thread listener(listenMgr);



	while (true) {
		clientChat->chatStream();
	}

	system("pause");
	return 0;
}


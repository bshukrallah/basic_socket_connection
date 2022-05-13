#include <iostream>
#include "Client.h"


//client

int main() {
	std::unique_ptr<chatClient> clientChat = std::make_unique<chatClient>();

	clientChat->createSocket();

	int port = 55555;
	std::string ipInput = "127.0.0.1";

	clientChat->serverConnect(ipInput, port);

	while (true) {
		clientChat->chatStream();
	}

	system("pause");
	return 0;
}


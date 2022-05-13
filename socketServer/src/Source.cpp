#include <iostream>
#include "Server.h"


//server

int main() {

	std::unique_ptr<chatServer> chatServ = std::make_unique<chatServer>();

	int port = 55555;

	chatServ->bindSocket(port);
	chatServ->listeningService();

	while (true) {
		chatServ->chatStream();
	}

	system("pause");
}
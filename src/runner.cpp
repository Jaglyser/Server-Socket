#include "server.h"
#include <algorithm>
#include <iostream>
#include <memory.h>
#include <memory>
#include "runner.h"

void Runner::run(unique_ptr<Server> server){
	signal(SIGINT, Runner::closeConnectionHandler);
	mServerInstance = std::move(server);
	mServerInstance->accept_request();
}

void Runner::closeConnectionHandler(int signum) {
	cout << "\n\rServer is shutting down" << endl;
	mServerInstance->closeConnection();
	exit(signum);
}

std::unique_ptr<Server> Runner::mServerInstance;


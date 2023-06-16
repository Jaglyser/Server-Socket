#include "server.h"
#include <algorithm>
#include <iostream>
#include <memory.h>
#include <memory>


using namespace std;
class Runner {

public: 
	static unique_ptr<Server> mServerInstance;

	static void run(unique_ptr<Server> server){
		signal(SIGINT, Runner::closeConnectionHandler);
		mServerInstance = move(server);
		mServerInstance->accept_request();
	}

	static void closeConnectionHandler(int signum) {
		cout << "Server is shutting down" << endl;
		mServerInstance->closeConnection();
		exit(signum);
	}


private:
	bool isRunning = false;

};

std::unique_ptr<Server> Runner::mServerInstance;


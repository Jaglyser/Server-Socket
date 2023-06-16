#ifndef RUNNER
#define RUNNER
#include "server.h"
#include <algorithm>
#include <iostream>
#include <memory.h>
#include <memory>


using namespace std;
class Runner {
public: 
	static void run(unique_ptr<Server> server);

	static void closeConnectionHandler(int signum); 

private:
	bool isRunning = false;

};

#endif

#ifndef SERVER
#define SERVER

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <memory>

#include <stdio.h>
#include <signal.h>

using std::unique_ptr;


class Server {


private:
	int server_socket; 
	int bind_addr;
	bool listening = true; 

public:
	static unique_ptr<Server> create(); 

	int create_socket(); 

	void bind_socket(); 

	void accept_request(); 

	void closeConnection(); 

};
#endif

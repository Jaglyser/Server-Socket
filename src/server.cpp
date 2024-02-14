#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <memory>
#include "server.h"

using std::unique_ptr;
using std::make_unique;

#define PORT 8082

unique_ptr<Server> Server::create() {
	auto server = make_unique<Server>();
	server->create_socket();
	server->bind_socket();
	return server;
}


int Server::create_socket() {
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
	this->server_socket = server_socket;  
	return server_socket;
}

void Server::bind_socket() {
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(PORT);
	this->bind_addr = bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
	listen(server_socket, 3);
} 

void Server::accept_request() {
	while(this->listening) {
		struct sockaddr_in client_address;
		socklen_t addrlen = sizeof(client_address);
		int client_socket = accept(server_socket, (struct sockaddr *)&client_address, &addrlen);
		// send data to the client
		const char *message = "HTTP/1.1 200 OK\r\n"
			"Content-Type: text/html\r\n"
			"Content-Length: 13\r\n" 
			"Accept-Ranges: bytes\r\n"
			"Connection: close\r\n"
			"\r\n"
		"Hello, World!";
		send(client_socket, message, strlen(message), 0);
	}
}

void Server::closeConnection() {
	this->listening = false;
	close(this->server_socket);
}


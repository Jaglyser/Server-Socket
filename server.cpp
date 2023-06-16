#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <memory>
#include "server.h"

#include <stdio.h>
#include <signal.h>



using std::unique_ptr;
using std::make_unique;


class Server {


private:
	int port = 8080;
	int server_socket; 
	int bind_addr;
	bool listening = true; 

public:

	static unique_ptr<Server> create() {
		auto server = make_unique<Server>();
		server->create_socket();
		server->bind_socket();
		return server;
	}


	int create_socket() {
		int server_socket = socket(AF_INET, SOCK_STREAM, 0);
		this->server_socket = server_socket;  
		return server_socket;
	}

	void bind_socket() {
		struct sockaddr_in server_address;
		server_address.sin_family = AF_INET;
		server_address.sin_addr.s_addr = INADDR_ANY;
		server_address.sin_port = htons(8080);
		this->bind_addr = bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
		listen(server_socket, 3);
	} 

	void accept_request() {

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

	void closeConnection() {
		this->listening = false;
		close(this->server_socket);
	}

};


	int create_socket() {
		int server_socket = socket(AF_INET, SOCK_STREAM, 0);
		this->server_socket = server_socket;  
		return server_socket;
	}

	void bind_socket() {
		struct sockaddr_in server_address;
		server_address.sin_family = AF_INET;
		server_address.sin_addr.s_addr = INADDR_ANY;
		server_address.sin_port = htons(8080);
		this->bind_addr = bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
		listen(server_socket, 3);
	} 

	void accept_request() {

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

	void closeConnection() {
		this->listening = false;
		close(this->server_socket);
	}

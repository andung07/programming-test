//
// Created by andung on 2019-05-07.
//

#include "TCPClient.h"

#define MAX_BUFFER 4096

TCPClient::TCPClient(std::string hostname, int port) {
	_hostname = hostname;
	_port = port;
}

int TCPClient::Init() {
	struct sockaddr_in server_addr;
	struct hostent *server;

	server = gethostbyname(_hostname.c_str());

	if (server == nullptr) {
		syslog(LOG_ERR, "no such host!");
		return -1;
	}

	bzero((char*) &server_addr, sizeof(server_addr));

	_sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (_sockfd < 0) {
		syslog(LOG_ERR, "Error opening socket!");
		return -1;
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(_port);

	bcopy((char*) server->h_addr, (char*) &server_addr.sin_addr.s_addr, server->h_length);

	int retval = connect(_sockfd, (struct sockaddr*) &server_addr, sizeof(server_addr));

	if (retval < 0) {
		syslog(LOG_ERR, "Failed opening a socket connection to the server!");
		return -1;
	}

	return 0;
}

int TCPClient::Read(std::string &message) {
	char buffer[MAX_BUFFER];
	bzero(buffer, MAX_BUFFER);

	int readbyte = read(_sockfd, buffer, MAX_BUFFER);

	message = buffer;

	if (readbyte < 0) {
		syslog(LOG_ERR, "Failed reading from the socket connection!");
		return -1;
	} else {
		return 0;
	}
}

int TCPClient::Write(std::string message) {
	int written = write(_sockfd, message.c_str(), message.length());

	if (written < 0) {
		syslog(LOG_ERR, "Failed writing to the socket connection!");
		return -1;
	} else {
		return 0;
	}
}


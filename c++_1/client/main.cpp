#include <iostream>
#include <syslog.h>
#include "TCPClient.h"

// Port 3111 python server
// Port 2999 c++ server
// This client can be used to test question 4 & 5

#define HOSTNAME "localhost"
#define PORT 3111
#define COMMAND "usec#crawl#https://www.kth.se/en#student"

int main() {
	TCPClient tcpClient(HOSTNAME, PORT);

	if (tcpClient.Init() == 0) {

		tcpClient.Write(COMMAND);

		std::string reply;
		int retval = tcpClient.Read(reply);

		if (retval == 0) {
			std::cout << reply << std::endl;
		} else {
			std::cout << "TCP READ FAILED!" << std::endl;
		}

	} else {
		syslog(LOG_ERR, "Error initializing the TCPClient!");
		exit(-1);
	}
}

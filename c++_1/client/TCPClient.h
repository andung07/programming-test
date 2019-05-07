//
// Created by andung on 2019-05-07.
//

#ifndef CLIENT_TCPCLIENT_H
#define CLIENT_TCPCLIENT_H

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string>
#include <syslog.h>

class TCPClient {

public:
    TCPClient(std::string hostname, int port);
    int Init();
    int Write(std::string message);
    int Read(std::string &message);

private:
    std::string _hostname;
    int _port;
    int _sockfd;

};


#endif //CLIENT_TCPCLIENT_H

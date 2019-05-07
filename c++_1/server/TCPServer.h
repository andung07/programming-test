//
// Created by andung on 2019-05-06.
//

#ifndef SERVER_TCPSERVER_H
#define SERVER_TCPSERVER_H

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <pthread.h>

class TCPServer {

public:
    TCPServer(int listeningPort);
    int Init();
    void Start();

private:
    int _listeningPort;
    int _sockfd;
    pthread_t _thread;
    static void* ReceivingTask(void* arg);

};


#endif //SERVER_TCPSERVER_H

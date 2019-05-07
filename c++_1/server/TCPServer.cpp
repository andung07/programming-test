//
// Created by andung on 2019-05-06.
//

#include "TCPServer.h"
#include <syslog.h>
#include <iostream>
#include "ScriptLauncher.h"

#define MAX_BUFFER 4096

TCPServer::TCPServer(int listeningPort) {
    _listeningPort = listeningPort;
}


int TCPServer::Init() {
    struct sockaddr_in server_addr;

    _sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (_sockfd < 0) {
        syslog(LOG_ERR, "Error opening socket!");
        return -1;
    }

    bzero((char*) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(_listeningPort);

    int retval = bind(_sockfd, (struct sockaddr*) &server_addr, sizeof(server_addr));

    if (retval < 0) {
        syslog(LOG_ERR, "Error in binding the socket!");
        return -1;
    }

    listen(_sockfd, 5);

    return 0;
}

void TCPServer::Start() {

    while(true) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        int newsockfd = accept(_sockfd, (struct sockaddr*) &client_addr, &client_len);

        if (newsockfd < 0) {
            syslog(LOG_ERR, "Error in accepting the connection!");
        }

        pthread_create(&_thread, NULL, &ReceivingTask, (void *) &newsockfd);
    }
}

void* TCPServer::ReceivingTask(void *arg) {

    int newsockfd = *(int*) arg;

    char buffer[MAX_BUFFER];
    bzero(buffer, MAX_BUFFER);

    pthread_detach(pthread_self());

    while(true) {
        int received = read(newsockfd, buffer, MAX_BUFFER);

        if (received < 0) {
            syslog(LOG_ERR, "Error in reading the received packet!");
        } else if (received == 0) {
            // Connection closed by the client
            close(newsockfd);
            break;
        } else {
            std::string output;
            int retval = ScriptLauncher::Execute(buffer, output);

            if (retval != 0) {
                output = "Command Failed!";
            }

            write(newsockfd, output.c_str(), output.length());

            bzero(buffer, MAX_BUFFER);
        }
    }

    return 0;
}


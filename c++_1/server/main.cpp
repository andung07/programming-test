/*
 * Listening on port 2999
 *
 * Waiting for a packet with format #usec#crawl#url#keyword#
 * Execute crawl.sh using received parameters
 * Forward the output to the client
 *
 */

#include <iostream>
#include <syslog.h>
#include "TCPServer.h"

#define LISTENING_PORT 2999

int main() {

    TCPServer tcpserver(LISTENING_PORT);

    if (tcpserver.Init() == 0) {
        tcpserver.Start();
    } else {
        syslog(LOG_ERR, "Error initializing the TCPServer!");
        exit(-1);
    }

}
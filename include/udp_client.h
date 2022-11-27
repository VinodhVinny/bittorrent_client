#ifndef _UDP_CLIENT_
#define _UDP_CLIENT_

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class UDPClient {
public:
    std::string address;
    int port;

    UDPClient(const std::string &address, int port);

private:
    int sockfd;
    struct sockaddr_in dest_addr;
};

#endif

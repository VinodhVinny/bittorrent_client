#include "../include/udp_client.h"

#include <cstring>

UDPClient::UDPClient(const std::string &address, int port) : address(address), port(port) {
    if ((this->sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        std::cerr << "Socker creation failed\n";
        exit(EXIT_FAILURE);
    }

    memset(&this->dest_addr, 0, sizeof(this->dest_addr));

    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(this->port);
    dest_addr.sin_addr.s_addr =
}

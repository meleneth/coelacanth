#ifndef UDPSOCKET_HPP
#define UDPSOCKET_HPP

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define UDPLISTENMAXBUFLEN 100

namespace Coelacanth {

class UDPSocket {
  public:
    UDPSocket();
    ~UDPListener();
    void recv();
    void listen(std::string hostname, std::string port);
    void connect_to(std::string hostname, std::string port);
    void send(std::string message);
int sockfd;
struct addrinfo hints, *servinfo, *p;
int rv;
int numbytes;
struct sockaddr_storage their_addr;
char buf[UDPLISTENMAXBUFLEN];
socklen_t addr_len;
char s[INET6_ADDRSTRLEN];
};

}
#endif

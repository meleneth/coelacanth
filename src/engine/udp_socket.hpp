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

#define UDPSOCKETMAXBUFLEN 255

#include "data_buffer.hpp"

namespace Coelacanth {

class UDPSocket {
public:
  UDPSocket();
  ~UDPSocket();

  void recv();
  void listen(int port);
  void connect_to(std::string hostname, int port);
  void send(std::string message);

  struct sockaddr_in myaddr;
  struct sockaddr_in remoteaddr;
  socklen_t addrlen = sizeof(remoteaddr);
  int fd;
  DataBuffer buffer;
};

} // namespace Coelacanth
#endif

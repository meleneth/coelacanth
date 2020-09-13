#include "easylogging++.h"

#include <udp_socket.hpp>

using namespace Coelacanth;

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa) {
  if (sa->sa_family == AF_INET) {
    return &(((struct sockaddr_in *)sa)->sin_addr);
  }

  return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

UDPSocket::UDPSocket() : buffer(UDPSOCKETMAXBUFLEN) {}

UDPSocket::~UDPSocket() {}

void UDPSocket::connect_to(std::string hostname, int port) {
  /* create a socket */

  if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    LOG(INFO) << "socket created";

  /* bind it to all local addresses and pick any port number */

  memset((char *)&myaddr, 0, sizeof(myaddr));
  myaddr.sin_family = AF_INET;
  myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  myaddr.sin_port = htons(0);

  if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
    LOG(ERROR) << "connect_to bind failed";
    return;
  }

  /* now define remaddr, the address to whom we want to send messages */
  /* For convenience, the host address is expressed as a numeric IP address */
  /* that we will convert to a binary format via inet_aton */

  memset((char *)&remoteaddr, 0, sizeof(remoteaddr));
  remoteaddr.sin_family = AF_INET;
  remoteaddr.sin_port = htons(port);
  if (inet_aton(hostname.c_str(), &remoteaddr.sin_addr) == 0) {
    LOG(ERROR) << "inet_aton() failed";
    exit(1);
  }
}

void UDPSocket::listen(int port) {
  /* create a UDP socket */

  if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("cannot create socket\n");
    return;
  }

  /* bind the socket to any valid IP address and a specific port */

  memset((char *)&myaddr, 0, sizeof(myaddr));
  myaddr.sin_family = AF_INET;
  myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  myaddr.sin_port = htons(port);

  if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
    LOG(ERROR) << "bind failed";
    return;
  }
}

void UDPSocket::recv() {
  if ((buffer.active_length = recvfrom(fd, buffer.storage, buffer.buffer_length - 1, 0,
                          (struct sockaddr *)&remoteaddr, &addrlen)) == -1) {
    LOG(ERROR) << "recvfrom";
    exit(1);
  }
  buffer.storage[buffer.active_length] = 0; // nothing like corrupting the data we just downloaded
}

void UDPSocket::send(std::string message) {
  ssize_t sentlen = sendto(fd, message.c_str(), message.length(), 0,
                        (struct sockaddr *)&remoteaddr, addrlen);
  if (sentlen == -1 ) {
    LOG(ERROR) << "talker: sendto";
    exit(1);
  }
}

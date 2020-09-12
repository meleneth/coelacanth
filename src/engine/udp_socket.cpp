#include "easylogging++.h"

#include <udp_socket.hpp>

using namespace Coelacanth;

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

UDPSocket::UDPSocket(std::string hostname, std::string port)
{
  	memset(&hints, 0, sizeof hints);
  	hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
  	hints.ai_socktype = SOCK_DGRAM;
  	hints.ai_flags = AI_PASSIVE; // use my IP

  	if ((rv = getaddrinfo(NULL, port.c_str(), &hints, &servinfo)) != 0) {
  		LOG(ERROR) << "getaddrinfo: " << gai_strerror(rv);
  		return;
  	}

  	// loop through all the results and bind to the first we can
  	for(p = servinfo; p != NULL; p = p->ai_next) {
  		if ((sockfd = socket(p->ai_family, p->ai_socktype,
  				p->ai_protocol)) == -1) {
  			LOG(ERROR) << "listener: socket";
  			return;
  		}

  		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
  			close(sockfd);
  			LOG(ERROR) << "listener: bind";
  			return;
  		}

  		break;
  	}

  	if (p == NULL) {
  		LOG(ERROR) << "listener: failed to bind socket";
  		return;
  	}

  	freeaddrinfo(servinfo);


}

UDPSocket::~UDPSocket()
{
	close(sockfd);
}

void UDPSocket::recv()
{
  addr_len = sizeof their_addr;
	if ((numbytes = recvfrom(sockfd, buf, UDPLISTENMAXBUFLEN-1 , 0,
		(struct sockaddr *)&their_addr, &addr_len)) == -1) {
		LOG(ERROR) << "recvfrom";
		exit(1);
	}

	LOG(INFO) << "listener: got packet from " << inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
	LOG(INFO) << "listener: packet is " << numbytes << " bytes long";
	buf[numbytes] = '\0';
	LOG(INFO) << "listener: packet contains \"" << buf << "\"";

	close(sockfd);
}

UDPSocket::connect_to(std::string hostname, std::string port)
{
  	memset(&hints, 0, sizeof hints);
  	hints.ai_family = AF_UNSPEC;
  	hints.ai_socktype = SOCK_DGRAM;

  	if ((rv = getaddrinfo(hostname.c_str(), port.c_str(), &hints, &servinfo)) != 0) {
  		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
  		return 1;
  	}
  	// loop through all the results and make a socket
  	for(p = servinfo; p != NULL; p = p->ai_next) {
  		if ((sockfd = socket(p->ai_family, p->ai_socktype,
  				p->ai_protocol)) == -1) {
  			LOG(ERROR) << "talker: socket";
  			continue;
  		}
  		break;
  	}

  	if (p == NULL) {
  	  LOG(ERROR) << "talker: failed to create socket";
  		return 2;
  	}
    freeaddrinfo(servinfo);
}

void UDPSocket::send(std::string message)
{
  if ((numbytes = sendto(sockfd, message.c_str(), message.length(), 0,
			 p->ai_addr, p->ai_addrlen)) == -1) {
		LOG(ERROR) << "talker: sendto";
		exit(1);
	}
  LOG(INFO) << "talker: sent " << numbytes << " bytes to " << CONNECTHOST;
}

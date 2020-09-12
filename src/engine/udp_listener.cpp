#include "easylogging++.h"

#include "udp_listener.hpp"

UDPListener::UDPListener()
{

}

UDPListener::~UDPListener()
{

}

UDPListener::listen()
{
  	memset(&hints, 0, sizeof hints);
  	hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
  	hints.ai_socktype = SOCK_DGRAM;
  	hints.ai_flags = AI_PASSIVE; // use my IP

  	if ((rv = getaddrinfo(NULL, MYPORT, &hints, &servinfo)) != 0) {
  		LOG(ERROR) << "getaddrinfo: " << gai_strerror(rv);
  		return 1;
  	}

  	// loop through all the results and bind to the first we can
  	for(p = servinfo; p != NULL; p = p->ai_next) {
  		if ((sockfd = socket(p->ai_family, p->ai_socktype,
  				p->ai_protocol)) == -1) {
  			LOG(ERROR) << "listener: socket";
  			continue;
  		}

  		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
  			close(sockfd);
  			LOG(ERROR) << "listener: bind";
  			continue;
  		}

  		break;
  	}

  	if (p == NULL) {
  		LOG(ERROR) << "listener: failed to bind socket";
  		return 2;
  	}

  	freeaddrinfo(servinfo);

}

UDPListener::recv()
{
  addr_len = sizeof their_addr;
	if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1 , 0,
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

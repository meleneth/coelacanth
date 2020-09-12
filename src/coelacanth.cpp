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

#include "easylogging++.h"

#define CONNECTHOST "localhost"

#define MYPORT "4950"	// the port users will be connecting to
#define SERVERPORT "4950"	// the port users will be connecting to

#define MAXBUFLEN 100

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

INITIALIZE_EASYLOGGINGPP

int entry_serve() {
  LOG(INFO) << "starting serve";

  /*
    server = NetServer("localhost", 4850);
    server->listen();

    clients = Vector<NetClient>;

  */
	
	auto listener = UDPListener("localhost", SERVERPORT)
	listener.listen();

  LOG(INFO) << "listener: waiting to recvfrom...";

	listener.recv();

	return 0;
}

int entry_client(std::string name) {
  LOG(INFO) << "starting client " << name;
	int sockfd;
	struct addrinfo hints, *servinfo, *p;
	int rv;
	int numbytes;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;

	if ((rv = getaddrinfo(CONNECTHOST, SERVERPORT, &hints, &servinfo)) != 0) {
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

  std::string message = "HELO " + name;

	if ((numbytes = sendto(sockfd, message.c_str(), message.length(), 0,
			 p->ai_addr, p->ai_addrlen)) == -1) {
		LOG(ERROR) << "talker: sendto";
		exit(1);
	}

	freeaddrinfo(servinfo);

  LOG(INFO) << "talker: sent " << numbytes << " bytes to " << CONNECTHOST;
	close(sockfd);

	return 0;
}

int main(int argc, char *argv[]) {
  el::Loggers::configureFromGlobal("/home/meleneth/.logging.conf");

  if(argc > 1) {
    if(strcmp(argv[1], "serve") == 0) {
      entry_serve();
    }
    if (argc == 3) {
      if(strcmp(argv[1], "client") == 0) {
        entry_client(argv[2]);
      }
    }
  }
  LOG(INFO) << "ending program";
  return 0;
}

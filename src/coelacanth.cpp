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

#include "engine/udp_listener.hpp"


#define MYPORT 4950
// the port users will be connecting to
#define SERVERPORT 4950
#define SERVERPORTSTRING "4950"
// the port users will be connecting to

#define MAXBUFLEN 100

using namespace Coelacanth;

INITIALIZE_EASYLOGGINGPP

int entry_serve() {
  LOG(INFO) << "starting serve";
	UDPListener listener("localhost", "4095");
  LOG(INFO) << "listener: waiting to recvfrom...";
	listener.recv();

	return 0;
}

int entry_client(std::string name) {
  LOG(INFO) << "starting client " << name;
  UDPSocket sender();
  sender.connect_to("localhost", "4095")
  sender.send("HELO " + message)

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

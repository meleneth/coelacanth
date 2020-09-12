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

#include<list>
#include<sstream>

#include "coelacanth_types.hpp"
#include "engine/udp_socket.hpp"

using namespace Coelacanth;

INITIALIZE_EASYLOGGINGPP

UDPSocketList clients;

UDPSocket *client_for_listener(UDPSocket &listener) {
  for (auto client : clients) {
    if ( client->remoteaddr.sin_port == listener.remoteaddr.sin_port ) {
      return client;
    }
  }
  auto client = new UDPSocket();
  client->fd = listener.fd;
  client->remoteaddr = listener.remoteaddr;
  clients.push_back(client);
  return client;
}

void entry_serve() {
  LOG(INFO) << "starting serve";
  UDPSocket listener;

  listener.listen(4095);

  while(1) {
    LOG(INFO) << "[seRve] listener: waiting to recvfrom...";
    listener.recv();
    client_for_listener(listener);
    LOG(INFO) << "[seRve] server got: " << listener.buf;
    std::stringstream reply;
    reply << "WELCOME " << 42;
    for (auto client : clients) {
      client->send(reply.str());
    }
  }
}

void entry_client(std::string name) {
  LOG(INFO) << "[cLient] starting client " << name;
  UDPSocket sender;
  sender.connect_to("127.0.0.1", 4095);
  sender.send("ISAIDHELLO " + name);
  //sleep(1);
  sender.send("HELO " + name);
  //sleep(1);
  sender.send("ISAIDHELO " + name);
  //sleep(1);
  while(1) {
    LOG(INFO) << "[cLient] waiting to recvfrom...";
    sender.recv();
  }
}

int main(int argc, char *argv[]) {
  el::Loggers::configureFromGlobal("/home/meleneth/.logging.conf");

  if (argc > 1) {
    if (strcmp(argv[1], "serve") == 0) {
      entry_serve();
    }
    if (argc == 3) {
      if (strcmp(argv[1], "client") == 0) {
        entry_client(argv[2]);
      }
    }
  }
  LOG(INFO) << "ending program";
  return 0;
}

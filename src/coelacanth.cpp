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
#include "machine/ticker/ticker_machine.hpp"

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

void entry_heartbeat() {
  UDPSocket sender;
  LOG(INFO) << "can you feel my heartbeat";
  sender.connect_to("127.0.0.1", 4095);
  while(1) {
    sender.send("HEARTBEAT");
    usleep(2500000);
  }
}

void entry_serve() {
  LOG(INFO) << "starting serve";
  UDPSocket listener;

  listener.listen(4095);

  TickerMachine ticker;

  while(1) {
    LOG(INFO) << "[seRve] listener: waiting to recvfrom...";
    listener.recv();
    if (listener.buffer.starts_with("HELO ")) {
      std::string name = std::string((char *)listener.buffer.storage + 5);
//      LOG(INFO) << "[seRve] server got HELO for : " << name;

      client_for_listener(listener);
      // machine: ClientConnection
      // machine.event(listener.buffer)
  //    LOG(INFO) << "[seRve] server got: " << listener.buffer.storage;
      std::stringstream reply;
      reply << "WELCOME " << name;
      for (auto client : clients) {
        client->send(reply.str());
      }
    } else if (listener.buffer.starts_with("HEARTBEAT")) {
      ticker.tick();
      for (auto client : clients) {
        client->send("TICK tick_id");
      }
    } else {
      LOG(INFO) << "server says: get out of here with your " << listener.buffer.storage;
    }
  }
}

void entry_client(std::string name) {
  LOG(INFO) << "[cLient] starting client " << name;
  UDPSocket sender;
  sender.connect_to("127.0.0.1", 4095);
  sender.send("HELO " + name);
  while(1) {
    LOG(INFO) << "[cLient] waiting to recvfrom...";
    sender.recv();
    LOG(INFO) << "[cLient] "<< name <<" got: " << sender.buffer.storage;
  }
}

int main(int argc, char *argv[]) {
  el::Loggers::configureFromGlobal("/home/meleneth/.logging.conf");

  if (argc > 1) {
    if (strcmp(argv[1], "heartbeat") == 0) {
      entry_heartbeat();
    }
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

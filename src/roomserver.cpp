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
#include <assert.h>

#include<list>
#include<sstream>

#include<cxxopts.hpp>

#include "coelacanth_types.hpp"
#include "engine/udp_socket.hpp"
#include "machine/game/game_machine.hpp"
#include "machine/room_server/room_server_machine.hpp"

using namespace Coelacanth;

INITIALIZE_EASYLOGGINGPP

RoomServerMachineList clients;

RoomServerMachine* client_for_listener(UDPSocket &listener, GameMachine *running_game) {
  for (auto client : clients) {
    if ( client->socket.remoteaddr.sin_port == listener.remoteaddr.sin_port ) {
      return client;
    }
  }
  auto client = new RoomServerMachine(&listener, running_game);
  clients.push_back(client);
  return client;
}

void entry_roomserver(std::string name, int listen_port, int report_port) {
  UDPSocket sender;
  sender.connect_to("127.0.0.1", report_port);
  LOG(INFO) << "[roomserver] starting serve on port " << listen_port;

  UDPSocket listener;
  listener.listen(listen_port);

  GameMachine game;
  std::stringstream reply;
  reply << "SERVREADY " << listen_port;
  sender.send(reply.str());
  sender.send("ROOMREADY " + name);

  while(1) {
    LOG(INFO) << "[roomserver] listener: waiting to recvfrom...";
    listener.recv();
    LOG(INFO) << "[roomserver] listener: got";
    /*
    auto client = client_for_listener(listener, &game);
    client->parse_packet(listener.buffer, clients);
    */
  }
}

int main(int argc, const char *argv[]) {
  el::Loggers::configureFromGlobal(".logging.conf");

  cxxopts::Options options("roomserver", "Run a dungeon, be the DM see the world they said");

  options.add_options()
    ("l,listen_port", "Port number to listen to", cxxopts::value<int>())
    ("r,report_port", "Port number of CentralDispatch to report back to", cxxopts::value<int>())
    ("n,name", "name of room to serve", cxxopts::value<std::string>())
    ;

  auto result = options.parse(argc, argv);
  int listen_port = result["listen_port"].as<int>();
  int report_port = result["report_port"].as<int>();
  std::string name = result["name"].as<std::string>();

  entry_roomserver(name, listen_port, report_port);

  LOG(INFO) << "ending program";
  return 0;
}

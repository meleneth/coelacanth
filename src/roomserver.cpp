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

#include "client.hpp"
#include "coelacanth_types.hpp"
#include "engine/udp_socket.hpp"
#include "machine/game/game_machine.hpp"
#include "machine/ticker/ticker_machine.hpp"

using namespace Coelacanth;

INITIALIZE_EASYLOGGINGPP


void entry_roomserver(std::string name, int listen_port, int report_port) {
  UDPSocket sender;
  sender.connect_to("127.0.0.1", report_port);
  LOG(INFO) << "[roomserver] starting serve on port " << listen_port;

  UDPSocket listener;
  listener.listen(listen_port);

  GameMachine game_machine;
  sender.send("SERVREADY server_token_id");
  sender.send("ROOMREADY " + name);

  while(1) {
    //LOG(INFO) << "[seRve] listener: waiting to recvfrom...";
    listener.recv();
    if (listener.buffer.starts_with("HELO ")) {
      std::string name = std::string((char *)listener.buffer.storage + 5);

      auto new_client = game_machine.client_for_listener(listener);
      new_client->player.name = name;
      std::stringstream reply;
      reply << "WELCOME " << name;
      for (auto client : game_machine.clients) {
        client->socket.send(reply.str());
      }
    } else if (listener.buffer.starts_with("HEARTBEAT")) {
      LOG(INFO) << "[roomserver] HEARTBEAT";
      //ticker.tick();
      game_machine.tick();
      for (auto client : game_machine.clients) {
        client->socket.send("TICK tick_id");
      }
    } else {
      LOG(INFO) << "server says: get out of here with your " << listener.buffer.storage;
    }
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

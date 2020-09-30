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

#include "client.hpp"
#include "coelacanth_types.hpp"
#include "engine/udp_socket.hpp"
#include "machine/game/game_machine.hpp"
#include "machine/ticker/ticker_machine.hpp"

using namespace Coelacanth;

INITIALIZE_EASYLOGGINGPP

#include<cxxopts.hpp>

void entry_heartbeat(int port_no, int delay) {
  UDPSocket sender;
  LOG(INFO) << "can you feel my heartbeat: " << port_no << " every " << delay;
  sender.connect_to("127.0.0.1", port_no);
  while(1) {
    LOG(INFO) << "[hbx] send HEARTBEAT";
    sender.send("HEARTBEAT");
    usleep(delay);
  }
}

int main(int argc, const char *argv[]) {
  el::Loggers::configureFromGlobal(".logging.conf");

  cxxopts::Options options("worldserver", "Bounce users to a newly spawned dungeon");

  options.add_options()
    ("p,port", "Port number to listen on for new connections", cxxopts::value<int>())
    ("d,delay", "delay time between heartbeat 2500000", cxxopts::value<int>())
    ;

  auto result = options.parse(argc, argv);
  int port_no = result["port"].as<int>();
  int delay = result["delay"].as<int>();
  entry_heartbeat(port_no, delay);
  LOG(INFO) << "ending heartbeat program";
  return 0;
}

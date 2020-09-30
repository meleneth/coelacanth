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

void entry_client(int port_no, std::string name) {
  LOG(INFO) << "[cLient] starting client " << name << " on port " << port_no;
  UDPSocket sender;
  sender.connect_to("127.0.0.1", port_no);
  sender.send("HELO " + name);
  while(1) {
    //LOG(INFO) << "[cLient] waiting to recvfrom...";
    sender.recv();
    LOG(INFO) << "[cLient] "<< name <<" got: " << sender.buffer.storage;
  }
}

int main(int argc, const char *argv[]) {
  el::Loggers::configureFromGlobal(".logging.conf");

  cxxopts::Options options("coelacanth", "Connect as a user to the game");
  options.add_options()
    ("p,port", "Port number to connect to", cxxopts::value<int>())
    ("u,name", "Name of player to connect as", cxxopts::value<std::string>())
    ;

  auto result = options.parse(argc, argv);
  int port_no = result["port"].as<int>();
  std::string name = result["name"].as<std::string>();

  entry_client(port_no, name);
  return 0;
}

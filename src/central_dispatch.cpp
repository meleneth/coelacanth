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
#include<string>
#include<sstream>

#include<spawn.h>

#include "coelacanth_types.hpp"
#include "engine/udp_socket.hpp"
#include "machine/game/game_machine.hpp"
#include "machine/ticker/ticker_machine.hpp"
#include "machine/central_dispatch/central_dispatch_machine.hpp"

using namespace Coelacanth;

#define CENTRAL_DISPATCH_PORT 12393

INITIALIZE_EASYLOGGINGPP

CentralDispatchMachineList clients;

int next_port();
CentralDispatchMachine* client_for_listener(UDPSocket& listener);
void start_world_server(std::string name);
void entry_central_dispatch();

CentralDispatchMachine* client_for_listener(UDPSocket &listener) {
  for (auto client : clients) {
    LOG(INFO) << "[cDp] existing client";
    if ( client->socket.remoteaddr.sin_port == listener.remoteaddr.sin_port ) {
      return client;
    }
  }
  LOG(INFO) << "[cDp] adding new client";
  auto client = new CentralDispatchMachine(&listener);
  clients.push_back(client);
  return client;
}

void entry_central_dispatch() {
  UDPSocket listener;
  listener.listen(CENTRAL_DISPATCH_PORT);
  LOG(INFO) << "[cDp] Listening on port " << CENTRAL_DISPATCH_PORT;

  start_world_server("USWest2");

  while(1) {
    listener.recv();

    auto client = client_for_listener(listener);
    client->parse_packet(listener.buffer, clients);
  }
}

int next_port()
{
  static int new_port = CENTRAL_DISPATCH_PORT + 24;
  new_port = new_port + 1;
  return new_port;
}

void start_world_server(std::string name)
{
  LOG(INFO) << "[cDp] Starting worldserver " << name;

  std::string world_server_port = std::to_string(next_port());

  std::string listen_port = std::to_string(next_port());
  std::string report_port = std::to_string(CENTRAL_DISPATCH_PORT);

	int pid = fork();

	if (pid == 0)
	{
      sleep(1);
			execl("./bin/worldserver", "./bin/worldserver", "-l", listen_port.c_str(), "-r", report_port.c_str(), "-t", "some_token", (const char *) 0);
			std::cout << "Exec error: " << errno << ", " << strerror(errno) << '\n';
			exit(1);
	}

  listen_port = std::to_string(next_port());
	pid = fork();

  if (pid == 0)
	{
      sleep(3);
			execl("./bin/roomserver", "./bin/roomserver", "-l", listen_port.c_str(), "-r", report_port.c_str(), "-n", "The_Brick_Road", (const char *) 0);
			std::cout << "Exec error: " << errno << ", " << strerror(errno) << '\n';
			exit(1);
	}
	pid = fork();
	if (pid == 0)
	{
      sleep(5);
			execl("./bin/coelacanth", "./bin/coelacanth", "-u", "MelX", "-p", listen_port.c_str(), (const char *) 0);
			std::cout << "Exec error: " << errno << ", " << strerror(errno) << '\n';
			exit(1);
	}
	pid = fork();
	if (pid == 0)
	{
      sleep(6);
			execl("./bin/coelacanth", "./bin/coelacanth", "-u", "zYz", "-p", listen_port.c_str(), (const char *) 0);
			std::cout << "Exec error: " << errno << ", " << strerror(errno) << '\n';
			exit(1);
	}

	pid = fork();
	if (pid == 0)
	{
      sleep(7);
			execl("./bin/coelacanth", "./bin/coelacanth", "-u", "DocVentur", "-p", listen_port.c_str(), (const char *) 0);
			std::cout << "Exec error: " << errno << ", " << strerror(errno) << '\n';
			exit(1);
	}
	pid = fork();
	if (pid == 0)
	{   sleep(8);
			execl("./bin/heartbeat", "./bin/heartbeat", "-d", "2500000", "-p", listen_port.c_str(), (const char *) 0);
			std::cout << "Exec error: " << errno << ", " << strerror(errno) << '\n';
			exit(1);
	}

}

int main(int argc, char *argv[]) {
  el::Loggers::configureFromGlobal(".logging.conf");

  entry_central_dispatch();

  LOG(INFO) << "ending program";
  return 0;
}

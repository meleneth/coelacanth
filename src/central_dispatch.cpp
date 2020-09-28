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

#include "client.hpp"
#include "coelacanth_types.hpp"
#include "engine/udp_socket.hpp"
#include "machine/game/game_machine.hpp"
#include "machine/ticker/ticker_machine.hpp"

using namespace Coelacanth;

#define CENTRAL_DISPATCH_PORT 12393

INITIALIZE_EASYLOGGINGPP

int next_port()
{
  static int new_port = CENTRAL_DISPATCH_PORT + 24;
  new_port = new_port + 1;
  return new_port;
}

UDPSocketList clients;

UDPSocket* client_for_listener(UDPSocket &listener) {
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

void start_world_server(std::string name) 
{
  LOG(INFO) << "Starting worldserver " << name;

  std::string world_server_port = std::to_string(next_port());
  
  std::string listen_port = std::to_string(next_port());
  std::string report_port = std::to_string(CENTRAL_DISPATCH_PORT);

	int pid = fork();
	if (pid == 0)
	{
			execl("./bin/worldserver", "./bin/worldserver", "-l", listen_port.c_str(), "-r", report_port.c_str(), "-t", "some_token", (const char *) 0);
			std::cout << "Exec error: " << errno << ", " << strerror(errno) << '\n';
			exit(1);
	}

  listen_port = std::to_string(next_port());
	pid = fork();
	if (pid == 0)
	{
			execl("./bin/roomserver", "./bin/roomserver", "-l", listen_port.c_str(), "-r", report_port.c_str(), "-n", "The_Brick_Road", (const char *) 0);
			std::cout << "Exec error: " << errno << ", " << strerror(errno) << '\n';
			exit(1);
	}

	pid = fork();
	if (pid == 0)
	{
			execl("./bin/coelacanth", "./bin/coelacanth", "-u", "MelX", "-p", listen_port.c_str(), (const char *) 0);
			std::cout << "Exec error: " << errno << ", " << strerror(errno) << '\n';
			exit(1);
	}

	pid = fork();
	if (pid == 0)
	{
			execl("./bin/coelacanth", "./bin/coelacanth", "-u", "zYz", "-p", listen_port.c_str(), (const char *) 0);
			std::cout << "Exec error: " << errno << ", " << strerror(errno) << '\n';
			exit(1);
	}

	pid = fork();
	if (pid == 0)
	{
			execl("./bin/coelacanth", "./bin/coelacanth", "-u", "DocVentur", "-p", listen_port.c_str(), (const char *) 0);
			std::cout << "Exec error: " << errno << ", " << strerror(errno) << '\n';
			exit(1);
	}

	pid = fork();
	if (pid == 0)
	{
			execl("./bin/heartbeat", "./bin/heartbeat", "-d", "2500000", "-p", report_port.c_str(), (const char *) 0);
			std::cout << "Exec error: " << errno << ", " << strerror(errno) << '\n';
			exit(1);
	}

}

// Start the Main World Server with appropriate arguments
// provide service that opens new world / room servers
void entry_central_dispatch() {
  //CentralDispatchMachine central_dispatch;
  // Start a WorldServer, so game clients have something to connect to
  // Listen for requests from servers
  UDPSocket listener;
  listener.listen(CENTRAL_DISPATCH_PORT);

  start_world_server("USWest2");

  while(1) {
//    LOG(INFO) << "[cDp] listener: waiting to recvfrom...";
    listener.recv();
//    LOG(INFO) << "[cDp] listener.recv()";
    LOG(INFO) << "[cDp] " << std::string((char *)listener.buffer.storage);
    LOG(INFO) << std::string((char *)listener.buffer.storage);
    if (listener.buffer.starts_with("SERVREADY ")) {
      std::string name = std::string((char *)listener.buffer.storage + 10);
      LOG(INFO) << "Cleanly got ";
      LOG(INFO) << name;
      client_for_listener(listener);
    } else if (listener.buffer.starts_with("HEARTBEAT")) {
      LOG(INFO) << "Passing HEARTBEAT to all clients..";
      for (auto client : clients) {
        LOG(INFO) << "Passing HEARTBEAT to client";
        client->send("HEARTBEAT beat_id");
      }
    } else {
      LOG(INFO) << "central_dispatch says: get out of here with your " << listener.buffer.storage;
    }
  }

}

int main(int argc, char *argv[]) {
  el::Loggers::configureFromGlobal(".logging.conf");

  entry_central_dispatch();

  LOG(INFO) << "ending program";
  return 0;
}

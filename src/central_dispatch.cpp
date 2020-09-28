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

void run_in_background(std::string command, std::string arguments) {
	int pid = fork();
	if (pid == 0)
	{
			execl(command.c_str(), arguments.c_str(), nullptr);
			std::cout << "Exec error: " << errno << ", " << strerror(errno) << '\n';
			exit(1);
	}
	return;	
}

void start_world_server(std::string name) 
{

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

	pid = fork();
	if (pid == 0)
	{
			execl("./bin/heartbeat", "./bin/hearbeat", "-d", "2500000", "-p", report_port.c_str(), (const char *) 0);
			std::cout << "Exec error: " << errno << ", " << strerror(errno) << '\n';
			exit(1);
	}

	pid = fork();
	if (pid == 0)
	{
			execl("./bin/coelacanth", "./bin/coelacanth", "-u", "MelX", "-p", world_server_port.c_str(), (const char *) 0);
			std::cout << "Exec error: " << errno << ", " << strerror(errno) << '\n';
			exit(1);
	}
	pid = fork();
	if (pid == 0)
	{
			execl("./bin/coelacanth", "./bin/coelacanth", "-u", "zYz", "-p", world_server_port.c_str(), (const char *) 0);
			std::cout << "Exec error: " << errno << ", " << strerror(errno) << '\n';
			exit(1);
	}
	pid = fork();
	if (pid == 0)
	{
			execl("./bin/coelacanth", "./bin/coelacanth", "-u", "DocVentur", "-p", world_server_port.c_str(), (const char *) 0);
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
    //LOG(INFO) << "[seRve] listener: waiting to recvfrom...";
    listener.recv();
    if (listener.buffer.starts_with("HELLO ")) {
      std::string name = std::string((char *)listener.buffer.storage + 6);
      LOG(INFO) << "Cleanly got ";
      LOG(INFO) << name;
    } else {
      LOG(INFO) << "server says: get out of here with your " << listener.buffer.storage;
    }
  }

}

int main(int argc, char *argv[]) {
  el::Loggers::configureFromGlobal(".logging.conf");

  entry_central_dispatch();

  LOG(INFO) << "ending program";
  return 0;
}

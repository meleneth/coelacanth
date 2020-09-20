#include "game_machine.hpp"

#include "client.hpp"

using namespace Coelacanth;

GameMachine::GameMachine()
{
}

GameMachine::~GameMachine()
{
}

Client* GameMachine::client_for_listener(UDPSocket &listener) {
  for (auto client : clients) {
    if ( client->socket.remoteaddr.sin_port == listener.remoteaddr.sin_port ) {
      return client;
    }
  }
  auto client = new Client(listener);
  clients.push_back(client);
  return client;
}

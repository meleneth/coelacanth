#include "game_machine.hpp"

#include "client.hpp"
#include "enemy.hpp"
#include "game_machine_state_combat.hpp"

using namespace Coelacanth;

GameMachine::GameMachine()
{
  state_ = new GameMachineStateCombat();
  create_enemy();
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

void GameMachine::tick()
{
  auto new_state = state_->tick(*this);
  if(new_state) {
    state_->onExit();
    delete state_;
    new_state->onEnter();
    state_ = new_state;
  }
}

void GameMachine::create_enemy()
{
  enemy = new Enemy("Slug");
  enemy->stats.xp = 5;
  enemy->stats.attack = 5;
  enemy->stats.health = 20;
}

#include <sstream>

#include <client.hpp>
#include <enemy.hpp>

#include "game_machine_state_combat.hpp"
#include "game_machine_state_enemy_died.hpp"


using namespace Coelacanth;

GameMachineStateCombat::GameMachineStateCombat()
{
}

GameMachineStateCombat::~GameMachineStateCombat()
{
}

GameMachineState* GameMachineStateCombat::tick(GameMachine& machine)
{
  for(auto client : machine.clients) {
    client->player.hit(*machine.enemy);
    if(machine.enemy->stats.is_dead()) {
      LOG(INFO) << "LETHAL BLOW!";
      std::stringstream message;
      message << "KILLED " << machine.enemy->name;
      client->socket.send(message.str());
      return new GameMachineStateEnemyDied();
    }
  }
  return nullptr;
}

void GameMachineStateCombat::onEnter()
{
}

void GameMachineStateCombat::onExit()
{
}

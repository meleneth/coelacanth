#include <sstream>

#include <random_selector.hpp>

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
  for(auto player : machine.players) {
    player->hit(*machine.enemy);
    if(machine.enemy->stats.is_dead()) {
      LOG(INFO) << "LETHAL BLOW!";
      std::stringstream message;
      //message << "KILLED " << machine.enemy->name;
      //client->socket.send(message.str());
      return new GameMachineStateEnemyDied();
    }
  }
  //  LOG(INFO) << "GOING IN!";
  if(machine.players.size()) {
    auto target = random_selector<Player*> (machine.players);
    std::stringstream message;
    machine.enemy->hit(*target);
    if(target->stats.is_dead()) {
      LOG(INFO) << "PLAYER KILLED!";
      std::stringstream message;
      //message << "KILLEDBY " << machine.enemy->name;
      //target->socket.send(message.str());
      //target->player.stats.health = target->player.stats.max_health;
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

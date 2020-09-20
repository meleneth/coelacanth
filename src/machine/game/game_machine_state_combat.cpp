#include "game_machine_state_combat.hpp"

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
    client->player.hit(machine.enemy);
    if(machine.enemy.is_dead()) {
      return new GameMachineStateEnemyDied()
    }
  }
}

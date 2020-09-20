#include "game_machine_state_enemy_died.hpp"

#include "game_machine_state_enemy_died.hpp"

using namespace Coelacanth;

GameMachineStateEnemyDied::GameMachineStateEnemyDied()
{
}

GameMachineStateEnemyDied::~GameMachineStateEnemyDied()
{
}

void GameMachineStateEnemyDied::onEnter()
{

}

GameMachineState* GameMachineStateEnemyDied::tick(GameMachine& machine)
{
  delete machine.enemy;
  machine.create_enemy();
  return new GameMachineStateCombat();
}

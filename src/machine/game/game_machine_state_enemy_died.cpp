#include <enemy.hpp>

#include "game_machine_state_enemy_died.hpp"
#include "game_machine_state_combat.hpp"

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

void GameMachineStateEnemyDied::onExit()
{

}

GameMachineState* GameMachineStateEnemyDied::tick(GameMachine& machine)
{
  delete machine.enemy;
  machine.create_enemy();
  return new GameMachineStateCombat();
}

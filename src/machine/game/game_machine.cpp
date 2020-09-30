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

void GameMachine::tick()
{
  possible_transition(state_->tick(*this));
}

void GameMachine::possible_transition(GameMachineState *new_state)
{
  if(new_state) {
    state_->onExit();
    delete state_;
    state_ = new_state;
    new_state->onEnter();
  }
}

void GameMachine::create_enemy()
{
  enemy = new Enemy("Slug");
  enemy->stats.xp = 5;
  enemy->stats.attack = 5;
  enemy->stats.health = 50;
}

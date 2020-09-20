#include <stdlib.h>

#include "player.hpp"
#include "enemy.hpp"

using namespace Coelacanth;

Player::Player()
{
  this->name = "NotSetPlayerName";
}

Player::~Player()
{
}

void Player::hit(Enemy& enemy)
{
  int dmg_amount = (rand() % stats.attack) + 1;
  LOG(INFO) << "Player " << name << " dealt " << dmg_amount << " to " << enemy.name;
  enemy.stats.health = enemy.stats.health - dmg_amount;
}

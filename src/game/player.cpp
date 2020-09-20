#include <stdlib.h>

#include "player.hpp"

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
  enemy.stats.health = enemy.stats.health - (rand() % (stats.attack + 1));
}

#include "enemy.hpp"
#include "player.hpp"

using namespace Coelacanth;

Enemy::Enemy(std::string name)
{
  this->name = name;
}

Enemy::~Enemy()
{
}

void Enemy::hit(Player& player)
{
  int dmg_amount = (rand() % stats.attack) + 1;
  player.stats.health = player.stats.health - dmg_amount;
  LOG(INFO) << "Enemy " << name << " dealt " << dmg_amount << " to " << player.name << "(" << player.stats.health << " left)";
}

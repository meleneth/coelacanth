#include "stats.hpp"

using namespace Coelacanth;

Stats::Stats()
{
  max_health = 100;
  health = max_health;
  level = 1;
  xp = 0;
  attack = 5;
}

Stats::~Stats()
{
}

bool Stats::is_dead()
{
  return health <= 0;
}

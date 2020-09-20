#ifndef STATS_HPP
#define STATS_HPP

namespace Coelacanth {

class Stats {
  public:
    Stats();
    ~Stats();

    int health;
    int max_health;
    int xp;
    int attack;
    int level;

    bool is_dead();
};

}

#endif

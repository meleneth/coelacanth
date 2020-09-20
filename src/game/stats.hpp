#ifndef STATS_HPP
#define STATS_HPP

namespace Coelacanth {

class Stats {
  public:
    Stats();
    ~Stats();

    int health;

    bool is_dead();
};

}

#endif

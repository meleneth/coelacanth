#ifndef ENEMY_HPP
#define ENEMY_HPP

#include<string>

#include "coelacanth_types.hpp"
#include "stats.hpp"

namespace Coelacanth {

class Enemy {
  public:
    Enemy();
    ~Enemy();

    std::string name;
    Stats stats;
};

}

#endif

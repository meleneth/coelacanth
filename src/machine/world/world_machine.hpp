#ifndef WORLD_MACHINE_HPP
#define WORLD_MACHINE_HPP

#include <memory>

namespace Coelacanth {

class WorldMachine {
  public:
    WorldMachine();
    ~WorldMachine();

    void tick();
    bool is_end() const;

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

}

#endif

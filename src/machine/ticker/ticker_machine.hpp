#ifndef TICKER_MACHINE_HPP
#define TICKER_MACHINE_HPP

#include <memory>

namespace Coelacanth {

class TickerMachine {
  public:
    TickerMachine();
    ~TickerMachine();

    void tick();
    bool is_tick() const;
    bool is_tock() const;

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

}

#endif

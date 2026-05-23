#include "ticker_machine.hpp"

#include <boost/sml.hpp>

#include "easylogging++.h"

using namespace Coelacanth;
namespace sml = boost::sml;

namespace {
struct TickEvent {};
struct TickState {};
struct TockState {};

struct TickerTransitions {
  auto operator()() const {
    using namespace sml;
    return make_transition_table(
      *state<TockState> + event<TickEvent> / [] { LOG(INFO) << "onEnter(Tick)"; } = state<TickState>,
       state<TickState> + event<TickEvent> / [] { LOG(INFO) << "onEnter(Tock)"; } = state<TockState>
    );
  }
};
}

struct TickerMachine::Impl {
  sml::sm<TickerTransitions> sm;
};

TickerMachine::TickerMachine()
  : impl_(std::make_unique<Impl>())
{
}

TickerMachine::~TickerMachine()
{
}

void TickerMachine::tick()
{
  impl_->sm.process_event(TickEvent{});
}

bool TickerMachine::is_tick() const
{
  return impl_->sm.is(sml::state<TickState>);
}

bool TickerMachine::is_tock() const
{
  return impl_->sm.is(sml::state<TockState>);
}

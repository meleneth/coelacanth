#include "world_machine.hpp"

#include <boost/sml.hpp>

using namespace Coelacanth;
namespace sml = boost::sml;

namespace {
struct TickEvent {};
struct ConstructState {};
struct PopulateState {};
struct SimulateState {};
struct EndState {};

struct WorldTransitions {
  auto operator()() const {
    using namespace sml;
    return make_transition_table(
      *state<ConstructState> + event<TickEvent> = state<PopulateState>,
       state<PopulateState> + event<TickEvent> = state<SimulateState>,
       state<SimulateState> + event<TickEvent> = state<EndState>,
       state<EndState> + event<TickEvent> = state<EndState>
    );
  }
};
}

struct WorldMachine::Impl {
  sml::sm<WorldTransitions> sm;
};

WorldMachine::WorldMachine()
  : impl_(std::make_unique<Impl>())
{
}

WorldMachine::~WorldMachine()
{
}

void WorldMachine::tick()
{
  impl_->sm.process_event(TickEvent{});
}

bool WorldMachine::is_end() const
{
  return impl_->sm.is(sml::state<EndState>);
}

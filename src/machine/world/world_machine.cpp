#include "world_machine.hpp"

#include <boost/sml.hpp>
#include <eventpp/callbacklist.h>
#include <variant>

using namespace Coelacanth;
namespace sml = boost::sml;

namespace {
struct Tick {};
using WorldEvent = std::variant<Tick>;

struct ConstructState {};
struct PopulateState {};
struct SimulateState {};
struct EndState {};

struct WorldTransitions {
  auto operator()() const {
    using namespace sml;
    return make_transition_table(
      *state<ConstructState> + event<Tick> = state<PopulateState>,
       state<PopulateState> + event<Tick> = state<SimulateState>,
       state<SimulateState> + event<Tick> = state<EndState>,
       state<EndState> + event<Tick> = state<EndState>
    );
  }
};
}

struct WorldMachine::Impl {
  Impl() {
    events.append([this](const WorldEvent& event) {
      std::visit([this](const auto& typed_event) {
        sm.process_event(typed_event);
      }, event);
    });
  }

  void publish(const WorldEvent& event) {
    events(event);
  }

  sml::sm<WorldTransitions> sm;
  eventpp::CallbackList<void(const WorldEvent&)> events;
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
  impl_->publish(Tick{});
}

bool WorldMachine::is_end() const
{
  return impl_->sm.is(sml::state<EndState>);
}

#include "ticker_machine.hpp"

#include <boost/sml.hpp>
#include <eventpp/callbacklist.h>
#include <variant>

#include "easylogging++.h"

using namespace Coelacanth;
namespace sml = boost::sml;

namespace {
struct Tick {};
using TickerEvent = std::variant<Tick>;

struct TickState {};
struct TockState {};

struct TickerTransitions {
  auto operator()() const {
    using namespace sml;
    return make_transition_table(
      *state<TockState> + event<Tick> / [] { LOG(INFO) << "onEnter(Tick)"; } = state<TickState>,
       state<TickState> + event<Tick> / [] { LOG(INFO) << "onEnter(Tock)"; } = state<TockState>
    );
  }
};
}

struct TickerMachine::Impl {
  Impl() {
    events.append([this](const TickerEvent& event) {
      std::visit([this](const auto& typed_event) {
        sm.process_event(typed_event);
      }, event);
    });
  }

  void publish(const TickerEvent& event) {
    events(event);
  }

  sml::sm<TickerTransitions> sm;
  eventpp::CallbackList<void(const TickerEvent&)> events;
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
  impl_->publish(Tick{});
}

bool TickerMachine::is_tick() const
{
  return impl_->sm.is(sml::state<TickState>);
}

bool TickerMachine::is_tock() const
{
  return impl_->sm.is(sml::state<TockState>);
}

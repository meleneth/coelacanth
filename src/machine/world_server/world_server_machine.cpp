#include "world_server_machine.hpp"

#include <boost/sml.hpp>
#include <eventpp/callbacklist.h>
#include <variant>

using namespace Coelacanth;
namespace sml = boost::sml;

namespace {
struct ParsePacket {
  DataBuffer& buffer;
};
using WorldServerEvent = std::variant<ParsePacket>;

struct WaitingState {};
struct LoginState {};
struct RecallState {};
struct RoomJoinState {};
struct WelcomeState {};

struct WorldServerTransitions {
  auto operator()() const {
    using namespace sml;
    return make_transition_table(
      *state<WaitingState> + event<ParsePacket> = state<WaitingState>
    );
  }
};
}

struct WorldServerMachine::Impl {
  Impl() {
    events.append([this](const WorldServerEvent& event) {
      std::visit([this](const auto& typed_event) {
        sm.process_event(typed_event);
      }, event);
    });
  }

  void publish(const WorldServerEvent& event) {
    events(event);
  }

  sml::sm<WorldServerTransitions> sm;
  eventpp::CallbackList<void(const WorldServerEvent&)> events;
};

WorldServerMachine::WorldServerMachine(UDPSocket* server_socket)
  : socket(server_socket),
    impl_(std::make_unique<Impl>())
{
}

WorldServerMachine::~WorldServerMachine()
{
}

void WorldServerMachine::parse_packet(DataBuffer& buffer)
{
  impl_->publish(ParsePacket{buffer});
}

bool WorldServerMachine::is_waiting() const
{
  return impl_->sm.is(sml::state<WaitingState>);
}

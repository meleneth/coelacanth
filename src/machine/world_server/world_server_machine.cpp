#include "world_server_machine.hpp"

#include <boost/sml.hpp>

using namespace Coelacanth;
namespace sml = boost::sml;

namespace {
struct ParsePacketEvent {
  DataBuffer& buffer;
};
struct WaitingState {};
struct LoginState {};
struct RecallState {};
struct RoomJoinState {};
struct WelcomeState {};

struct WorldServerTransitions {
  auto operator()() const {
    using namespace sml;
    return make_transition_table(
      *state<WaitingState> + event<ParsePacketEvent> = state<WaitingState>
    );
  }
};
}

struct WorldServerMachine::Impl {
  sml::sm<WorldServerTransitions> sm;
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
  impl_->sm.process_event(ParsePacketEvent{buffer});
}

bool WorldServerMachine::is_waiting() const
{
  return impl_->sm.is(sml::state<WaitingState>);
}

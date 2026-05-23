#include "central_dispatch_machine.hpp"

#include <boost/sml.hpp>

#include "data_buffer.hpp"

using namespace Coelacanth;
namespace sml = boost::sml;

namespace {
struct ParsePacketEvent {
  DataBuffer& buffer;
  CentralDispatchMachineList& clients;
};
struct HeartbeatEvent {
  CentralDispatchMachineList& clients;
};

struct WaitingState {};
struct HeartbeatState {};
struct ConnectedState {};
struct DeadState {};

struct CentralDispatchTransitions {
  auto operator()() const {
    using namespace sml;
    auto heartbeat_packet = [](const ParsePacketEvent& event) {
      return event.buffer.starts_with("HEARTBEAT");
    };
    auto servready = [](CentralDispatchMachine& machine) {
      return machine.listener->buffer.starts_with("SERVREADY ");
    };
    auto connect_server = [] {
      LOG(INFO) << "[cD:Ms] SERVREADY disabled, fix listener_port";
    };
    auto reject_packet = [](CentralDispatchMachine& machine) {
      LOG(INFO) << "[cD:Ms] watch out it's the cops says: get out of here with your "
                << machine.listener->buffer.storage;
    };
    auto pass_heartbeat = [](CentralDispatchMachine& machine, const ParsePacketEvent& event) {
      LOG(INFO) << "[cDp] got heartbeat, sending to attached servers";
      machine.heartbeat(event.clients);
    };
    auto send_heartbeat = [](CentralDispatchMachine& machine) {
      LOG(INFO) << "[cDp] <Connected> " << &machine << " Passing along HEARTBEAT to "
                << machine.reply_socket.myaddr.sin_port;
      machine.send("HEARTBEAT");
    };
    return make_transition_table(
      *state<WaitingState> + event<ParsePacketEvent> [heartbeat_packet] = state<HeartbeatState>,
       state<WaitingState> + event<ParsePacketEvent> [servready] / connect_server = state<ConnectedState>,
       state<WaitingState> + event<ParsePacketEvent> / reject_packet,
       state<ConnectedState> + event<ParsePacketEvent> [heartbeat_packet] / pass_heartbeat,
       state<HeartbeatState> + event<ParsePacketEvent> [heartbeat_packet] / pass_heartbeat,
       state<ConnectedState> + event<HeartbeatEvent> / send_heartbeat
    );
  }
};
}

struct CentralDispatchMachine::Impl {
  explicit Impl(CentralDispatchMachine& machine) : sm(machine) {}
  sml::sm<CentralDispatchTransitions> sm;
};

CentralDispatchMachine::CentralDispatchMachine(UDPSocket* server_socket)
  : impl_(std::make_unique<Impl>(*this))
{
  listener = server_socket;
  socket.fd = server_socket->fd;
  socket.remoteaddr = server_socket->remoteaddr;
}

CentralDispatchMachine::~CentralDispatchMachine()
{
}

void CentralDispatchMachine::send(std::string message)
{
  reply_socket.send(message);
}

void CentralDispatchMachine::heartbeat(CentralDispatchMachineList& clients)
{
  for(auto client : clients) {
    client->impl_->sm.process_event(HeartbeatEvent{clients});
  }
}

void CentralDispatchMachine::parse_packet(DataBuffer& buffer, CentralDispatchMachineList& clients)
{
  impl_->sm.process_event(ParsePacketEvent{buffer, clients});
}

bool CentralDispatchMachine::is_connected() const
{
  return impl_->sm.is(sml::state<ConnectedState>);
}

bool CentralDispatchMachine::is_heartbeat() const
{
  return impl_->sm.is(sml::state<HeartbeatState>);
}

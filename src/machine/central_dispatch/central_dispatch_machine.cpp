#include "central_dispatch_machine.hpp"

#include <boost/sml.hpp>
#include <eventpp/callbacklist.h>
#include <variant>

#include "data_buffer.hpp"

using namespace Coelacanth;
namespace sml = boost::sml;

namespace {
struct ParsePacket {
  DataBuffer& buffer;
  CentralDispatchMachineList& clients;
};
struct Heartbeat {
  CentralDispatchMachineList& clients;
};
using CentralDispatchEvent = std::variant<ParsePacket, Heartbeat>;

struct WaitingState {};
struct HeartbeatState {};
struct ConnectedState {};
struct DeadState {};

struct CentralDispatchTransitions {
  auto operator()() const {
    using namespace sml;
    auto heartbeat_packet = [](const ParsePacket& event) {
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
    auto pass_heartbeat = [](CentralDispatchMachine& machine, const ParsePacket& event) {
      LOG(INFO) << "[cDp] got heartbeat, sending to attached servers";
      machine.heartbeat(event.clients);
    };
    auto send_heartbeat = [](CentralDispatchMachine& machine) {
      LOG(INFO) << "[cDp] <Connected> " << &machine << " Passing along HEARTBEAT to "
                << machine.reply_socket.myaddr.sin_port;
      machine.send("HEARTBEAT");
    };
    return make_transition_table(
      *state<WaitingState> + event<ParsePacket> [heartbeat_packet] = state<HeartbeatState>,
       state<WaitingState> + event<ParsePacket> [servready] / connect_server = state<ConnectedState>,
       state<WaitingState> + event<ParsePacket> / reject_packet,
       state<ConnectedState> + event<ParsePacket> [heartbeat_packet] / pass_heartbeat,
       state<HeartbeatState> + event<ParsePacket> [heartbeat_packet] / pass_heartbeat,
       state<ConnectedState> + event<Heartbeat> / send_heartbeat
    );
  }
};
}

struct CentralDispatchMachine::Impl {
  explicit Impl(CentralDispatchMachine& machine) : sm(machine) {
    events.append([this](const CentralDispatchEvent& event) {
      std::visit([this](const auto& typed_event) {
        sm.process_event(typed_event);
      }, event);
    });
  }

  void publish(const CentralDispatchEvent& event) {
    events(event);
  }

  sml::sm<CentralDispatchTransitions> sm;
  eventpp::CallbackList<void(const CentralDispatchEvent&)> events;
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
    client->impl_->publish(Heartbeat{clients});
  }
}

void CentralDispatchMachine::parse_packet(DataBuffer& buffer, CentralDispatchMachineList& clients)
{
  impl_->publish(ParsePacket{buffer, clients});
}

bool CentralDispatchMachine::is_connected() const
{
  return impl_->sm.is(sml::state<ConnectedState>);
}

bool CentralDispatchMachine::is_heartbeat() const
{
  return impl_->sm.is(sml::state<HeartbeatState>);
}

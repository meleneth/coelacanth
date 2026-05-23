#include "room_server_machine.hpp"

#include <boost/sml.hpp>
#include <eventpp/callbacklist.h>
#include <sstream>
#include <variant>

#include "data_buffer.hpp"
#include "machine/game/game_machine.hpp"
#include "player.hpp"

using namespace Coelacanth;
namespace sml = boost::sml;

namespace {
struct ParsePacket {
  DataBuffer& buffer;
  RoomServerMachineList& clients;
};
struct Recall {};
struct Heartbeat {
  RoomServerMachineList& clients;
};
using RoomServerEvent = std::variant<ParsePacket, Recall, Heartbeat>;

struct WaitingState {};
struct ClientJoinState {};
struct ClientReadyState {};
struct HeartbeatState {};
struct MobFightState {};
struct StartState {};

struct RoomServerTransitions {
  auto operator()() const {
    using namespace sml;
    auto helo = [](const ParsePacket& event) {
      return event.buffer.starts_with("HELO ");
    };
    auto heartbeat_packet = [](const ParsePacket& event) {
      return event.buffer.starts_with("HEARTBEAT");
    };
    auto join_client = [](RoomServerMachine& machine, const ParsePacket& event) {
      std::string name = std::string(reinterpret_cast<char *>(event.buffer.storage) + 5);
      machine.player = new Player(name);
      machine.game->add_player(machine.player);
    };
    auto reject_packet = [](const ParsePacket& event) {
      LOG(INFO) << "server says: get out of here with your " << event.buffer.storage;
    };
    auto send_ticks = [](const ParsePacket& event) {
      LOG(INFO) << "[RS:SM] got HeartBEAT";
      for(auto client : event.clients) {
        client->send("TICK tick_id");
      }
    };
    return make_transition_table(
      *state<WaitingState> + event<ParsePacket> [helo] / join_client = state<ClientJoinState>,
       state<WaitingState> + event<ParsePacket> [heartbeat_packet] = state<HeartbeatState>,
       state<WaitingState> + event<ParsePacket> / reject_packet,
       state<HeartbeatState> + event<ParsePacket> / send_ticks,
       state<ClientJoinState> + event<Recall> = state<ClientJoinState>,
       state<ClientReadyState> + event<Recall> = state<ClientReadyState>,
       state<MobFightState> + event<Recall> = state<MobFightState>,
       state<StartState> + event<Recall> = state<StartState>
    );
  }
};
}

struct RoomServerMachine::Impl {
  explicit Impl(RoomServerMachine& machine) : sm(machine) {
    events.append([this](const RoomServerEvent& event) {
      std::visit([this](const auto& typed_event) {
        sm.process_event(typed_event);
      }, event);
    });
  }

  void publish(const RoomServerEvent& event) {
    events(event);
  }

  sml::sm<RoomServerTransitions> sm;
  eventpp::CallbackList<void(const RoomServerEvent&)> events;
};

RoomServerMachine::RoomServerMachine(UDPSocket *server_socket, GameMachine *running_game)
  : game(running_game),
    player(nullptr),
    impl_(std::make_unique<Impl>(*this))
{
  listener = server_socket;
  socket.fd = server_socket->fd;
  socket.remoteaddr = server_socket->remoteaddr;
}

RoomServerMachine::~RoomServerMachine()
{
}

void RoomServerMachine::send(std::string message)
{
  socket.send(message);
}

void RoomServerMachine::recall()
{
  impl_->publish(Recall{});
}

void RoomServerMachine::heartbeat(RoomServerMachineList& clients)
{
  for(auto client : clients) {
    client->impl_->publish(Heartbeat{clients});
  }
}

void RoomServerMachine::parse_packet(DataBuffer& buffer, RoomServerMachineList& clients)
{
  LOG(INFO) << "[RSM] got " << buffer.storage;
  impl_->publish(ParsePacket{buffer, clients});
}

bool RoomServerMachine::is_client_join() const
{
  return impl_->sm.is(sml::state<ClientJoinState>);
}

bool RoomServerMachine::is_heartbeat() const
{
  return impl_->sm.is(sml::state<HeartbeatState>);
}

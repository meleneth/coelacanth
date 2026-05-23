#include "room_server_machine.hpp"

#include <boost/sml.hpp>
#include <sstream>

#include "data_buffer.hpp"
#include "machine/game/game_machine.hpp"
#include "player.hpp"

using namespace Coelacanth;
namespace sml = boost::sml;

namespace {
struct ParsePacketEvent {
  DataBuffer& buffer;
  RoomServerMachineList& clients;
};
struct RecallEvent {};
struct HeartbeatEvent {
  RoomServerMachineList& clients;
};

struct WaitingState {};
struct ClientJoinState {};
struct ClientReadyState {};
struct HeartbeatState {};
struct MobFightState {};
struct StartState {};

struct RoomServerTransitions {
  auto operator()() const {
    using namespace sml;
    auto helo = [](const ParsePacketEvent& event) {
      return event.buffer.starts_with("HELO ");
    };
    auto heartbeat_packet = [](const ParsePacketEvent& event) {
      return event.buffer.starts_with("HEARTBEAT");
    };
    auto join_client = [](RoomServerMachine& machine, const ParsePacketEvent& event) {
      std::string name = std::string(reinterpret_cast<char *>(event.buffer.storage) + 5);
      machine.player = new Player(name);
      machine.game->add_player(machine.player);
    };
    auto reject_packet = [](const ParsePacketEvent& event) {
      LOG(INFO) << "server says: get out of here with your " << event.buffer.storage;
    };
    auto send_ticks = [](const ParsePacketEvent& event) {
      LOG(INFO) << "[RS:SM] got HeartBEAT";
      for(auto client : event.clients) {
        client->send("TICK tick_id");
      }
    };
    return make_transition_table(
      *state<WaitingState> + event<ParsePacketEvent> [helo] / join_client = state<ClientJoinState>,
       state<WaitingState> + event<ParsePacketEvent> [heartbeat_packet] = state<HeartbeatState>,
       state<WaitingState> + event<ParsePacketEvent> / reject_packet,
       state<HeartbeatState> + event<ParsePacketEvent> / send_ticks,
       state<ClientJoinState> + event<RecallEvent> = state<ClientJoinState>,
       state<ClientReadyState> + event<RecallEvent> = state<ClientReadyState>,
       state<MobFightState> + event<RecallEvent> = state<MobFightState>,
       state<StartState> + event<RecallEvent> = state<StartState>
    );
  }
};
}

struct RoomServerMachine::Impl {
  explicit Impl(RoomServerMachine& machine) : sm(machine) {}
  sml::sm<RoomServerTransitions> sm;
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
  impl_->sm.process_event(RecallEvent{});
}

void RoomServerMachine::heartbeat(RoomServerMachineList& clients)
{
  for(auto client : clients) {
    client->impl_->sm.process_event(HeartbeatEvent{clients});
  }
}

void RoomServerMachine::parse_packet(DataBuffer& buffer, RoomServerMachineList& clients)
{
  LOG(INFO) << "[RSM] got " << buffer.storage;
  impl_->sm.process_event(ParsePacketEvent{buffer, clients});
}

bool RoomServerMachine::is_client_join() const
{
  return impl_->sm.is(sml::state<ClientJoinState>);
}

bool RoomServerMachine::is_heartbeat() const
{
  return impl_->sm.is(sml::state<HeartbeatState>);
}

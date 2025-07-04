#include "room_server_machine_state.hpp"
#include "room_server_machine.hpp"

#include "room_server_machine_state_heartbeat.hpp"
#include "room_server_machine_state_client_join.hpp"

#include "data_buffer.hpp"
#include "player.hpp"
#include "machine/game/game_machine.hpp"

using namespace Coelacanth;

RoomServerMachineState::RoomServerMachineState()
{
}

RoomServerMachineState::~RoomServerMachineState()
{
}

void RoomServerMachineState::onEnter(RoomServerMachine& machine)
{
}

void RoomServerMachineState::onExit(RoomServerMachine& machine)
{
}

void RoomServerMachineState::heartbeat(RoomServerMachine& machine, RoomServerMachineList& clients)
{
}

RoomServerMachineState* RoomServerMachineState::parse_packet(RoomServerMachine& machine, DataBuffer& buffer, RoomServerMachineList& clients)
{
    if (buffer.starts_with("HELO ")) {
      std::string name = std::string((char *)buffer.storage + 5);
      machine.player = new Player(name);
      machine.game->add_player(machine.player);
      return new RoomServerMachineStateClientJoin();
      //auto new_client = game_machine.client_for_listener(listener);
      //new_client->player.name = name;
      std::stringstream reply;
      reply << "FAYKE WELCOME " << name;
      LOG(INFO) << reply.str();
      return nullptr;
      //for (auto client : game_machine.clients) {
      //  client->socket.send(reply.str());
      //}
    }
    if (buffer.starts_with("HEARTBEAT")) {
      LOG(INFO) << "[roomserver] HEARTBEAT";
      return new RoomServerMachineStateHeartbeat();
      //ticker.tick();
      //game_machine.tick();
      //for (auto client : game_machine.clients) {
      //  client->socket.send("TICK tick_id");
      //}
    } else {
      LOG(INFO) << "server says: get out of here with your " << buffer.storage;
    }
  LOG(INFO) << "[RSM] NO TRANSITION!";
  return nullptr;
}

RoomServerMachineState* RoomServerMachineState::recall(RoomServerMachine& machine)
{
  return nullptr;
}

#include "room_server_machine.hpp"

#include "room_server_machine_state.hpp"

using namespace Coelacanth;

RoomServerMachine::RoomServerMachine(UDPSocket *server_socket, GameMachine *running_game)
{
  listener = server_socket;
  game = running_game;
  player = nullptr;
  state_ = new RoomServerMachineState();
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

void RoomServerMachine::possible_transition(RoomServerMachineState* new_state)
{
  if(new_state) {
    state_->onExit(*this);
    delete state_;
    state_ = new_state;
    state_->onEnter(*this);
  }
}

void RoomServerMachine::recall()
{
  possible_transition(state_->recall(*this));
}

void RoomServerMachine::heartbeat(RoomServerMachineList& clients)
{
  for(auto client : clients) {
    client->state_->heartbeat(*client, clients);
  }
}

void RoomServerMachine::parse_packet(DataBuffer& buffer, RoomServerMachineList& clients)
{
  LOG(INFO) << "[RSM] got " << buffer.storage;
  possible_transition(state_->parse_packet(*this, buffer, clients));
}

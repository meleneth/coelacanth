#include "room_server_machine.hpp"

#include "room_server_machine_state.hpp"

using namespace Coelacanth;

RoomServerMachine::RoomServerMachine(UDPSocket *server_socket)
{
  listener = server_socket;
  state_ = new RoomServerMachineState();
  socket.fd = server_socket->fd;
  socket.remoteaddr = server_socket->remoteaddr;
}

RoomServerMachine::~RoomServerMachine()
{
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
    client->state_->heartbeat(*this, clients);
  }
}

void RoomServerMachine::parse_packet(DataBuffer& buffer, CentralDispatchMachineList& clients)
{
  possible_transition(state_->parse_packet(*this, buffer, clients));
}

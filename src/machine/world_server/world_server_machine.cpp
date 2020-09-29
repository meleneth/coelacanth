#include "world_server_machine.hpp"

#include "world_server_machine_state.hpp"

#include "udp_socket.hpp"

using namespace Coelacanth;

WorldServerMachine::WorldServerMachine(UDPSocket* server_socket)
{
  state_ = new WorldServerMachineState();
  socket->fd = server_socket->fd;
  socket->remoteaddr = server_socket->remoteaddr;
}

WorldServerMachine::~WorldServerMachine()
{
}

void WorldServerMachine::possible_transition(WorldServerMachineState* new_state)
{
  if(new_state) {
    state_->onExit(*this);
    delete state_;
    state_->onEnter(*this);
    state_ = new_state;
  }
}

void WorldServerMachine::parse_packet(DataBuffer* buffer)
{
  possible_transition(state_->parse_packet(*this, buffer));
}

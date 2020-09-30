#include "central_dispatch_machine.hpp"

#include <udp_socket.hpp>

#include "central_dispatch_machine_state.hpp"
#include "central_dispatch_machine_state_connected.hpp"

using namespace Coelacanth;

CentralDispatchMachine::CentralDispatchMachine(UDPSocket* server_socket)
{
  state_ = new CentralDispatchMachineStateConnected();
  socket.fd = server_socket->fd;
  socket.remoteaddr = server_socket->remoteaddr;
}

CentralDispatchMachine::~CentralDispatchMachine()
{
}

void CentralDispatchMachine::possible_transition(CentralDispatchMachineState* new_state)
{
  if(new_state) {
    state_->onExit(*this);
    delete state_;
    state_ = new_state;
    state_->onEnter(*this);
  }
}

void CentralDispatchMachine::parse_packet(DataBuffer& buffer, CentralDispatchMachineList& clients)
{
  possible_transition(state_->parse_packet(*this, buffer, clients));
}

#include "central_dispatch_machine_state.hpp"
#include "central_dispatch_machine_state_heartbeat.hpp"
#include "central_dispatch_machine_state_connected.hpp"
#include"data_buffer.hpp"

using namespace Coelacanth;

CentralDispatchMachineState::CentralDispatchMachineState()
{
}

CentralDispatchMachineState::~CentralDispatchMachineState()
{
}

void CentralDispatchMachineState::onEnter(CentralDispatchMachine& machine)
{
}

void CentralDispatchMachineState::onExit(CentralDispatchMachine& machine)
{
}

CentralDispatchMachineState* CentralDispatchMachineState::parse_packet(CentralDispatchMachine& machine, DataBuffer& buffer, CentralDispatchMachineList& clients)
{
  if(buffer.starts_with("HEARTBEAT")) {
    return new CentralDispatchMachineStateHeartbeat();
  }
  if (machine.listener->buffer.starts_with("SERVREADY ")) {
    std::string listener_port = (char *)machine.listener->buffer.storage + 10;
    LOG(INFO) << "[cD:Ms] " << &machine << " reply_to set to port " << std::stoi(listener_port);
    LOG(INFO) << " HEY SPARKY " << htons(11219);
    machine.reply_socket.connect_to("127.0.0.1", std::stoi(listener_port));
    LOG(INFO) << "[cD:Ms] " << &machine << " reply_to set to port -- " << machine.reply_socket.remoteaddr.sin_port;
    return new CentralDispatchMachineStateConnected();
  } else {
    LOG(INFO) << "[cD:Ms] watch out it's the cops says: get out of here with your " << machine.listener->buffer.storage;
  }
  return nullptr;
}

void CentralDispatchMachineState::heartbeat(CentralDispatchMachine& machine, CentralDispatchMachineList& clients)
{
}

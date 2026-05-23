#ifndef CENTRAL_DISPATCH_MACHINE_HPP
#define CENTRAL_DISPATCH_MACHINE_HPP

#include <memory>

#include "coelacanth_types.hpp"

#include "udp_socket.hpp"

namespace Coelacanth {

class CentralDispatchMachine {
  public:
    CentralDispatchMachine(UDPSocket *server_socket);
    ~CentralDispatchMachine();

    virtual void parse_packet(DataBuffer& buffer, CentralDispatchMachineList& clients);
    virtual void heartbeat(CentralDispatchMachineList& clients);

    void send(std::string message);
    bool is_connected() const;
    bool is_heartbeat() const;
    
    UDPSocket socket;
    UDPSocket reply_socket;

    UDPSocket *listener;

  private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};

}

#endif

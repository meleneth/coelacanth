#include "client.hpp"

using namespace Coelacanth;

Client::Client(UDPSocket& server_socket)
{
  socket.fd = server_socket.fd;
  socket.remoteaddr = server_socket.remoteaddr;
}

Client::~Client()
{
}

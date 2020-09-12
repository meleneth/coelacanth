use https://github.com/davidkristola/fluent-hsm-cpp

SPECS:
JOINED THE SERVER means you get a TICK from the server every 250ms

client commands
===============
HELO myname -- JOIN THE SERVER as myname
GOODBYE -- disconnect from the server (clean)
SWING targetid -- swing at target by id

server commands
===============
TICK tickid -- heartbeat
MONSTER typeid targetid -- a monster has appeared!

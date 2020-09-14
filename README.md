use https://github.com/davidkristola/fluent-hsm-cpp

SPECS:
JOINED THE SERVER means you get a TICK from the server every 250ms

client commands
===============
HELO myname -- JOIN THE SERVER as myname
SWING targetid -- swing at target by id
GOODBYE -- disconnect from the server (clean)

server commands
===============
WELCOME targetid -- server recognizes you and bids you welcome
TICK tickid -- heartbeat
MONSTER typeid targetid -- a monster has appeared!

#!/bin/bash

killall coelacanth

./bin/coelacanth serve &

sleep 1

./bin/coelacanth heartbeat &
./bin/coelacanth client Tom &
./bin/coelacanth client Dick &
./bin/coelacanth client Harry &



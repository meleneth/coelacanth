#!/bin/bash

killall coelacanth

./bin/coelacanth serve &

sleep 1

./bin/coelacanth heartbeat &
./bin/coelacanth client Tom &
./bin/coelacanth client Dick &
./bin/coelacanth client Harry &
./bin/coelacanth client Foo &
./bin/coelacanth client Bar &
./bin/coelacanth client Baz &
./bin/coelacanth client You &
./bin/coelacanth client Me &
./bin/coelacanth client Belgium &



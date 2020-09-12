#!/bin/bash

killall coelacanth

./bin/coelacanth serve &
./bin/coelacanth client Tom &
./bin/coelacanth client Dick &
./bin/coelacanth client Harry &



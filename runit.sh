#!/bin/bash

set -e

cmake --build build

./stop_processes.sh || true
cd build
./bin/central_dispatch

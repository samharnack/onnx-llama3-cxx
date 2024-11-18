#!/bin/bash
rm -rf build
mkdir -p build
cd build
cmake ..
cd ..
cmake --build build

./bin/cli "$@"
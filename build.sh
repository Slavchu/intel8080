#!/bin/bash

cmake -S . -B build
ln -s build/compile_commands.json .
cd build 
make -j$(nproc)

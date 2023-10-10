#!/bin/bash

# Clone the Emscripten SDK repository
git clone https://github.com/emscripten-core/emsdk.git

# Change the current directory to the emsdk directory
cd emsdk

# Run the emsdk installation script
./emsdk install latest

# Set the emsdk environment
./emsdk activate latest

# Activate PATH and other environment variables in the current terminal
source ./emsdk_env.sh
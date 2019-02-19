#!/bin/sh

# Install make and cmake.
sudo apt-get update; sudo apt-get install make cmake -y;

# Call the installer script.
./Scripts/Installers/${PLATFORM}-${ARCH}.sh
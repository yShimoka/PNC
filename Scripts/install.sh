#!/bin/sh

# Install zip, make and cmake.
sudo apt-get update; sudo apt-get install make cmake zip -y;

# Call the installer script.
./Scripts/Installers/${PLATFORM}-${ARCH}.sh
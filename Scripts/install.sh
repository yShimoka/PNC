#!/bin/sh

# Install make and cmake.
apt-get update; apt-get install make cmake -y;

# Call the installer script.
./Scripts/Installers/${PLATFORM}-${ARCH}.sh
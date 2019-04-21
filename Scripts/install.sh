#!/bin/bash
set -e

if [[ "$OSTYPE" == "linux-gnu" ]]; then
    # Install zip, make and cmake.
    sudo apt-get update; sudo apt-get install make cmake zip -y;
fi

# Call the installer script.
./Scripts/Installers/${PLATFORM}-${ARCH}.sh
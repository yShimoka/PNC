#!/bin/sh

sudo apt-get update -y

# Install gcc
sudo apt-get install gcc -y

# Install sdl2 dependencies
sudo apt-get install \
    libgles2-mesa-dev \
    libegl1-mesa-dev -y
    
# Install the sdl2 library.
sudo apt-get install \
    libsdl2-dev \
    libsdl2-ttf-dev \
    libsdl2-image-dev \
    libsdl2-mixer-dev -y

# Create a symbolic link for TTF, mixer and image.
sudo ln -s /usr/include/SDL2 /usr/include/SDL2_ttf
sudo ln -s /usr/include/SDL2 /usr/include/SDL2_mixer
sudo ln -s /usr/include/SDL2 /usr/include/SDL2_image
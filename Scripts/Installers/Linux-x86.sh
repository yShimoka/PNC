#!/bin/sh

apt-get update

# Install gcc
apt-get install gcc

# Install the sdl2 library.
apt-get install \
    libsdl2-dev \
    libsdl2-ttf-dev \
    libsdl2-image-dev \
    libsdl2-mixer-dev
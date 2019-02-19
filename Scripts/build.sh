#!/bin/sh

cmake . -DCMAKE_TOOLCHAIN_FILE=Scripts/Toolchains/${PLATFORM}-${ARCH}.cmake
make
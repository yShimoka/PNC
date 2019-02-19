#!/bin/sh

# Build the application.
cmake . -DCMAKE_TOOLCHAIN_FILE=Scripts/Toolchains/${PLATFORM}-${ARCH}.cmake
make

# Package the results.
mkdir -p Build/out
cp -r Assets/ Build/bin/
cd Build/bin
zip -r ../out/PNC-${MAJOR}.${MINOR}_${TRAVIS_BUILD_NUMBER}-${PLATFORM}_${ARCH}.zip *
cd ../..
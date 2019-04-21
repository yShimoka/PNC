#!/bin/sh

#!/bin/bash
set -e

# Build the application.
echo "${PLATFORM}-${ARCH}"
cmake . -DCMAKE_TOOLCHAIN_FILE=./Scripts/Toolchains/${PLATFORM}-${ARCH}.cmake
make

# Package the results. 
mkdir -p Build/out
cp -r Assets Build/bin/
cd Build/bin
zip -r ../out/PNC-${MAJOR}_${MINOR}_${TRAVIS_BUILD_NUMBER}-${PLATFORM}_${ARCH}.zip *
cd ../..
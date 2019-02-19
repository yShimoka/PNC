#!/bin/sh

# Install required utilities.
apt-get install curl mingw-w64 -y

# Download all the libraries.
mkdir -p Downloaded/Libraries
echo "Downloading libraries ..."
curl -s -o Downloaded/Libraries/SDL2.tar.gz https://www.libsdl.org/release/SDL2-devel-2.0.9-mingw.tar.gz
echo "SDL2 OK"
curl -s -o Downloaded/Libraries/SDL2_ttf.tar.gz https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-devel-2.0.15-mingw.tar.gz
echo "SDL2_ttf OK"
curl -s -o Downloaded/Libraries/SDL2_mixer.tar.gz https://libsdl.org/projects/SDL_mixer/release/SDL2_mixer-devel-2.0.4-mingw.tar.gz
echo "SDL2_mixer OK"
curl -s -o Downloaded/Libraries/SDL2_image.tar.gz https://libsdl.org/projects/SDL_image/release/SDL2_image-devel-2.0.4-mingw.tar.gz
echo "SDL2_image OK"

# Copy the libraries over.
mkdir -p Libraries/lib Libraries/bin Libraries/include
echo "Copying libraries locally ..."
tar -x -f Downloaded/Libraries/SDL2.tar.gz --directory=Libraries/lib SDL2-2.0.9/x86_64-w64-mingw32/lib/ --strip-components=3
tar -x -f Downloaded/Libraries/SDL2.tar.gz --directory=Libraries/include SDL2-2.0.9/x86_64-w64-mingw32/include/SDL2/ --strip-components=4
tar -x -f Downloaded/Libraries/SDL2.tar.gz --directory=Libraries/bin SDL2-2.0.9/x86_64-w64-mingw32/bin/ --strip-components=3

tar -x -f Downloaded/Libraries/SDL2_ttf.tar.gz --directory=Libraries/lib SDL2_ttf-2.0.15/x86_64-w64-mingw32/lib/ --strip-components=3
tar -x -f Downloaded/Libraries/SDL2_ttf.tar.gz --directory=Libraries/include SDL2_ttf-2.0.15/x86_64-w64-mingw32/include/SDL2/ --strip-components=4
tar -x -f Downloaded/Libraries/SDL2_ttf.tar.gz --directory=Libraries/bin SDL2_ttf-2.0.15/x86_64-w64-mingw32/bin/ --strip-components=3

tar -x -f Downloaded/Libraries/SDL2_mixer.tar.gz --directory=Libraries/lib SDL2_mixer-2.0.4/x86_64-w64-mingw32/lib/ --strip-components=3
tar -x -f Downloaded/Libraries/SDL2_mixer.tar.gz --directory=Libraries/include SDL2_mixer-2.0.4/x86_64-w64-mingw32/include/SDL2/ --strip-components=4
tar -x -f Downloaded/Libraries/SDL2_mixer.tar.gz --directory=Libraries/bin SDL2_mixer-2.0.4/x86_64-w64-mingw32/bin/ --strip-components=3

tar -x -f Downloaded/Libraries/SDL2_image.tar.gz --directory=Libraries/lib SDL2_image-2.0.4/x86_64-w64-mingw32/lib/ --strip-components=3
tar -x -f Downloaded/Libraries/SDL2_image.tar.gz --directory=Libraries/include SDL2_image-2.0.4/x86_64-w64-mingw32/include/SDL2/ --strip-components=4
tar -x -f Downloaded/Libraries/SDL2_image.tar.gz --directory=Libraries/bin SDL2_image-2.0.4/x86_64-w64-mingw32/bin/ --strip-components=3
echo "Done"

# Copy the dynamic libraries to the output result.
mkdir -p Build/bin
cp Libraries/bin/*.dll Build/bin/
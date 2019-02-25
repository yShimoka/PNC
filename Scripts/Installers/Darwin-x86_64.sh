#!/bin/sh

# Download all the frameworks.
mkdir -p Downloaded/Frameworks
echo "Downloading frameworks ..."
curl  -s -o Downloaded/Frameworks/SDL2.dmg       https://www.libsdl.org/release/SDL2-2.0.9.dmg
echo "SDL2 OK"
curl  -s -o Downloaded/Frameworks/SDL2_ttf.dmg   https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.15.dmg
echo "SDL2_ttf OK"
curl  -s -o Downloaded/Frameworks/SDL2_image.dmg https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.4.dmg
echo "SDL2_image OK"
curl  -s -o Downloaded/Frameworks/SDL2_mixer.dmg https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.4.dmg
echo "SDL2_mixer OK"

# Mount the images.
hdiutil attach -quiet Downloaded/Frameworks/SDL2.dmg
hdiutil attach -quiet Downloaded/Frameworks/SDL2_ttf.dmg
hdiutil attach -quiet Downloaded/Frameworks/SDL2_image.dmg
hdiutil attach -quiet Downloaded/Frameworks/SDL2_mixer.dmg

# Copy the frameworks over.
mkdir -p Frameworks
echo "Copying frameworks locally ..."
cp -r /Volumes/SDL2/SDL2.framework Frameworks/
cp -r /Volumes/SDL2_ttf/SDL2_ttf.framework Frameworks/
cp -r /Volumes/SDL2_image/SDL2_image.framework Frameworks/
cp -r /Volumes/SDL2_mixer/SDL2_mixer.framework Frameworks/
echo "Done"

# Unmount the images.
hdiutil detach -quiet /Volumes/SDL2 
hdiutil detach -quiet /Volumes/SDL2_ttf
hdiutil detach -quiet /Volumes/SDL2_image
hdiutil detach -quiet /Volumes/SDL2_mixer
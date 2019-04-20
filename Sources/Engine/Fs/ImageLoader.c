#include "Engine/Fs/ImageLoader.h"

#include "Engine/Rendering/Windows.h"

#include <stdio.h>

SDL_Texture* USG_IMG_loadFromFile(const char * path) {
    // Load the image from the file.
    SDL_Surface* img = IMG_Load(path);

    if (img) {
        fprintf(stdout, "Loaded image from : %s", path);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(_USG_WINMAN_getWindow()->pRenderer, img);
        SDL_FreeSurface(img);

        return texture;
    } else {
        fprintf(stderr, "Image loading error : %s", SDL_GetError());
        return NULL;
    }
}
#ifndef __USAGI_IMAGELOADER_H__
#define __USAGI_IMAGELOADER_H__

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "Engine/Tools/List.h"

struct USG_Texture {
    SDL_Texture* pTexture;
    const char * pPath;
};

USG_List _USG_IMG_getImgList();

struct USG_Texture* USG_IMG_loadFromFile(const char * path);

void USG_IMG_clear();


#endif /* __USAGI_IMAGELOADER_H__ */
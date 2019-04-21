#ifndef __USAGI_IMAGELOADER_H__
#define __USAGI_IMAGELOADER_H__

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "Engine/Tools/List.h"

USG_List _USG_IMG_getImgList();

SDL_Texture* USG_IMG_loadFromFile(const char * path);


#endif /* __USAGI_IMAGELOADER_H__ */
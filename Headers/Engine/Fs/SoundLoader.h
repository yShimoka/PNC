#ifndef __USAGI_SOUNDLOADER_H__
#define __USAGI_SOUNDLOADER_H__

#include "Engine/Tools/List.h"

#include <SDL2/SDL.h>
#include <SDL2_mixer/SDL_mixer.h>

USG_List _USG_MIX_getSFXList();

Mix_Chunk* USG_MIX_loadSFX();


#endif /* __USAGI_SOUNDLOADER_H__ */
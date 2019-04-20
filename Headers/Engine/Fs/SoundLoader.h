#ifndef __USAGI_SOUNDLOADER_H__
#define __USAGI_SOUNDLOADER_H__

#include "Engine/Tools/List.h"

#include <SDL2/SDL.h>
#include <SDL2_mixer/SDL_mixer.h>

struct USG_Sfx {
    Mix_Chunk* pSoundChunck;

    const char * pSfxPath;
};

USG_List _USG_MIX_getSFXList();

int USG_SFX_isSame(struct USG_Sfx* self, struct USG_Sfx* other);

struct USG_Sfx* USG_MIX_loadSFX(const char * sfxPath);

void USG_MIX_clear();


#endif /* __USAGI_SOUNDLOADER_H__ */
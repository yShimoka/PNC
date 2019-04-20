#include "Engine/Fs/SoundLoader.h"

#include <string.h>
#include <stdio.h>

USG_List _USG_MIX_getSFXList() {
    static USG_List listInstance = NULL;

    if (listInstance == NULL) {
        listInstance = USG_LIST_create();
    }

    return listInstance;
}

int USG_SFX_isSame(struct USG_Sfx* self, struct USG_Sfx* other) {
    return (strcmp(self->pSfxPath, other->pSfxPath) == 0);
}

struct USG_Sfx* USG_MIX_loadSFX(const char * sfxPath) {
    // Check if the sound was already laoded.
    struct USG_Node* head = *(_USG_MIX_getSFXList());

    while ((head != NULL) && USG_SFX_isSame(head->pContents, &((struct USG_Sfx){NULL, sfxPath}))) head = head->pNext;

    if (head != NULL) return head->pContents;

    Mix_Chunk* chunk = Mix_LoadWAV(sfxPath);

    if (chunk != NULL) {
        // Create a new SFX object.
        struct USG_Sfx* sfx = (struct USG_Sfx*)malloc(sizeof(struct USG_Sfx));

        sfx->pSoundChunck = chunk;
        sfx->pSfxPath = sfxPath;

        // Add it to the list.
        USG_LIST_append(_USG_MIX_getSFXList(), sfx);

        return sfx;
    } else {
        fprintf(stderr, "Could not load mix chunk: %s", SDL_GetError());
        return NULL;
    }
}

void _USG_SFX_clearSfx(void* sfx) {
    if (sfx != NULL) {
        Mix_FreeChunk(sfx);
    }
}

void USG_MIX_clear() {
    USG_LIST_forEach(_USG_MIX_getSFXList(), _USG_SFX_clearSfx);

    USG_LIST_clear(_USG_MIX_getSFXList());
}
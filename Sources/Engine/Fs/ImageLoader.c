#include "Engine/Fs/ImageLoader.h"

#include "Engine/Rendering/Windows.h"
#include "Engine/Tools/Allocator.h"

#include <string.h>
#include <stdio.h>

USG_List _USG_IMG_getImgList() {
    static USG_List list = NULL;

    if(list == NULL) {
        list = USG_LIST_create();
    }

    return list;
}

struct USG_Texture* USG_IMG_loadFromFile(const char * path) {
    // Seek the texture in the list.
    struct USG_Node* head = USG_LIST_findFirst(*_USG_IMG_getImgList());

    while (
        (head != NULL) &&
        (strcmp(path, ((struct USG_Texture *)(head->pContents))->pPath) != 0)
    ) head = head->pNext;

    if (head != NULL) return (struct USG_Texture *)(head->pContents);

    // Load the image from the file.
    SDL_Surface* img = IMG_Load(path);

    if (img != NULL) {
        SDL_Texture* sdlTexture = SDL_CreateTextureFromSurface(_USG_WINMAN_getWindow()->pRenderer, img);
        SDL_FreeSurface(img);

        // Store the image in a new object.
        struct USG_Texture * texture = (struct USG_Texture *)USG_allocate(sizeof(struct USG_Texture));

        texture->pPath = path;
        texture->pTexture = sdlTexture;

        USG_LIST_append(_USG_IMG_getImgList(), texture);

        return texture;
    } else {
        fprintf(stderr, "Image loading error : %s", SDL_GetError());
        return NULL;
    }
}

void _USG_IMG_clearTexture(void* element) {
    struct USG_Texture* texture = (struct USG_Texture *)element;

    SDL_DestroyTexture(texture->pTexture);

    USG_deallocate(texture);
}

void USG_IMG_clear() {
    USG_LIST_forEach(_USG_IMG_getImgList(), _USG_IMG_clearTexture);

    USG_LIST_clear(_USG_IMG_getImgList());
}
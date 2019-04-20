#include "Engine/Fs/FontLoader.h"

#include "Engine/Rendering/Windows.h"

#include <string.h>

USG_List _USG_FONT_getFontList() {
    static USG_List listInstance = NULL;

    if (listInstance == NULL) {
        listInstance = USG_LIST_create();
    }

    return listInstance;
}

int USG_FONT_isSame(struct USG_Font* self, struct USG_Font* other) {
    if (self->size == other->size) {
        if (strcmp(self->pFontPath, other->pFontPath) == 0) {
            return 1;
        }
    }

    return 0;
}

struct USG_Font* USG_FONT_getFont(const char * path, int size) {
    // Seek for the font in the list.
    struct USG_Node* head = *(_USG_FONT_getFontList());

    while ((head != NULL) && !(USG_FONT_isSame(head->pContents, &((struct USG_Font){NULL, path, size}))))
        head = head->pNext;
    
    if (head != NULL) return head->pContents;

    TTF_Font* font = TTF_OpenFont(path, size);

    if (font) {
        // Create a new usagi font.
        struct USG_Font* usgFont = (struct USG_Font*)malloc(sizeof(struct USG_Font));

        usgFont->pFont = font;
        usgFont->pFontPath = path;
        usgFont->size = size;

        // Add it to the list.
        USG_LIST_append(_USG_FONT_getFontList(), usgFont);

        return usgFont;
    } else {
        fprintf(stderr, "Could not open font: %s", SDL_GetError());
        return NULL;
    }
}

SDL_Texture* USG_FONT_render(const char * text, struct USG_Font* font, SDL_Color fgColor, SDL_Color bgColor) {
    // Create a new texture from the font.
    SDL_Surface* surface = TTF_RenderText_Shaded(font->pFont, text, fgColor, bgColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(_USG_WINMAN_getWindow()->pRenderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void _USG_FONT_clearFont(void* font) {
    if (font != NULL) {
        TTF_CloseFont(font);
    }
}

void USG_FONT_clear() {
    USG_LIST_forEach(_USG_FONT_getFontList(), _USG_FONT_clearFont);

    USG_LIST_clear(_USG_FONT_getFontList());
}
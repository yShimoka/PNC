#include "Engine/Fs/FontLoader.h"

#include "Engine/Rendering/Windows.h"
#include "Engine/Tools/Allocator.h"

#include <string.h>
#include <stdio.h>

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

struct USG_Vector USG_FONT_predictTextSize(const char * text, const char * path, int size) {
    // Get the font.
    struct USG_Font* font = USG_FONT_getFont(path, size);

    // Return the predicted size.
    int x, y;
    TTF_SizeText(font->pFont, text, &x, &y);
    return USG_VECTOR(x, y);
}

struct USG_Font* USG_FONT_getFont(const char * path, int size) {
    // Seek for the font in the list.
    struct USG_Node* head = *(_USG_FONT_getFontList());

    while (
        (head != NULL) && 
        !(USG_FONT_isSame(head->pContents, &((struct USG_Font){NULL, path, size})))
    )
        head = head->pNext;

    if (head != NULL) return head->pContents;

    TTF_Font* font = TTF_OpenFont(path, size);

    if (font) {
        // Create a new usagi font.
        struct USG_Font* usgFont = (struct USG_Font*)USG_allocate(1, sizeof(struct USG_Font));

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

SDL_Texture* USG_FONT_render(const char * text, struct USG_Font* font, SDL_Color fgColor) {
    // Create a new texture from the font.
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font->pFont, text, fgColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(_USG_WINMAN_getWindow()->pRenderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void _USG_FONT_clearFont(void* element) {
    struct USG_Font* font = (struct USG_Font*)element;
    
    TTF_CloseFont(font->pFont);
        
    USG_deallocate(font);
}

void USG_FONT_clear() {
    USG_LIST_forEach(_USG_FONT_getFontList(), _USG_FONT_clearFont);

    USG_LIST_clear(_USG_FONT_getFontList());
}

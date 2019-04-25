#ifndef __USAGI_FONTLOADER_H__
#define __USAGI_FONTLOADER_H__

#include "Engine/Tools/List.h"

#include <SDL2_ttf/SDL_ttf.h>

#include "Engine/Math/Vector.h"

struct USG_Font {
    TTF_Font* pFont;

    const char * pFontPath;
    int size;
};

USG_List _USG_FONT_getFontList();

struct USG_Vector USG_FONT_predictTextSize(const char * text, const char * path, int size);

int USG_FONT_isSame(struct USG_Font* self, struct USG_Font* other);

struct USG_Font* USG_FONT_getFont(const char * path, int size);

SDL_Texture* USG_FONT_render(const char * text, struct USG_Font* font, SDL_Color fgColor);

void USG_FONT_clear();

#endif /* __USAGI_FONTLOADER_H__ */
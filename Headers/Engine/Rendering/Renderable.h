#ifndef __USAGI_RENDERABLE_H__
#define __USAGI_RENDERABLE_H__

#include <SDL2/SDL.h>

#include "Engine/Tools/List.h"

enum USG_RenderableTypes {
    USG_RENDER_PRIMITIVE_SQUARE,
    USG_RENDER_TEXTURE
};

struct USG_UVCoords {
    float x, y, w, h;
};

struct USG_Renderable {
    enum USG_RenderableTypes type;

    SDL_Color color;

    SDL_Texture* pTexture;

    struct USG_UVCoords src;
    SDL_Rect dest;

};

USG_List _USG_RENDER_getRenderableList();

struct USG_Renderable* USG_RENDER_createSquarePrimitive(SDL_Color color, SDL_Rect size);
struct USG_Renderable* USG_RENDER_createTexture(SDL_Texture* texture, struct USG_UVCoords source, SDL_Rect dest);

void _USG_RENDER_clearElement(void* element);

void USG_RENDER_clear();

#endif /* __USAGI_RENDERABLE_H__ */
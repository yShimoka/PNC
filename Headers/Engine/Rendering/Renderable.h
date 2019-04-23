#ifndef __USAGI_RENDERABLE_H__
#define __USAGI_RENDERABLE_H__

#include <SDL2/SDL.h>

#include "Engine/Tools/List.h"
#include "Engine/Math/Rect.h"

struct USG_Layer;

enum USG_RenderableTypes {
    USG_RENDER_PRIMITIVE_SQUARE,
    USG_RENDER_TEXTURE
};

struct USG_Renderable {
    enum USG_RenderableTypes type;

    SDL_Color color;

    SDL_Texture* pTexture;

    struct USG_Rect src;
    struct USG_Rect dest;

    struct USG_Layer *pLayer;

    int bVisible;
};


struct USG_Renderable* USG_RENDER_createSquarePrimitive(SDL_Color color, struct USG_Rect size);
struct USG_Renderable* USG_RENDER_createTexture(SDL_Texture* texture, struct USG_Rect source, struct USG_Rect dest);

void _USG_RENDER_clearElement(void* element);

#endif /* __USAGI_RENDERABLE_H__ */
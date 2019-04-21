#include "Engine/Rendering/Renderable.h"
\
#include "Engine/Tools/Allocator.h"

struct USG_Renderable* USG_RENDER_createSquarePrimitive(SDL_Color color, SDL_Rect size) {
    // Create the element.
    struct USG_Renderable* nextObj = (struct USG_Renderable *)USG_allocate(sizeof(struct USG_Renderable));

    nextObj->type = USG_RENDER_PRIMITIVE_SQUARE;
    nextObj->dest = size;
    nextObj->color = color;

    // Return the object.
    return nextObj;
}

struct USG_Renderable* USG_RENDER_createTexture(SDL_Texture* texture, struct USG_UVCoords source, SDL_Rect dest) {
    // Create the element.
    struct USG_Renderable* nextObj = (struct USG_Renderable *)USG_allocate(sizeof(struct USG_Renderable));

    nextObj->type = USG_RENDER_TEXTURE;
    nextObj->pTexture = texture;
    nextObj->src = source;
    nextObj->dest = dest;

    // Return the object.
    return nextObj;
}

void _USG_RENDER_clearElement(void* element) {
    struct USG_Renderable* renderable = element;
    if (renderable != NULL) {
        USG_deallocate(renderable);
    }
}

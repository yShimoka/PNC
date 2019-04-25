#include "Engine/Rendering/Renderable.h"
\
#include "Engine/Tools/Allocator.h"

struct USG_Renderable* USG_RENDER_createSquarePrimitive(SDL_Color color, struct USG_Rect size) {
    // Create the element.
    struct USG_Renderable* nextObj = (struct USG_Renderable *)USG_allocate(1, sizeof(struct USG_Renderable));

    nextObj->type = USG_RENDER_PRIMITIVE_SQUARE;
    nextObj->dest = size;
    nextObj->color = color;
    nextObj->bVisible = 1;

    // Return the object.
    return nextObj;
}

struct USG_Renderable* USG_RENDER_createTexture(SDL_Texture* texture, struct USG_Rect source, struct USG_Rect dest) {
    // Create the element.
    struct USG_Renderable* nextObj = (struct USG_Renderable *)USG_allocate(1, sizeof(struct USG_Renderable));

    nextObj->type = USG_RENDER_TEXTURE;
    nextObj->pTexture = texture;
    nextObj->src = source;
    nextObj->dest = dest;
    nextObj->bVisible = 1;

    // Return the object.
    return nextObj;
}

void _USG_RENDER_clearElement(void* element) {
    struct USG_Renderable* renderable = element;
    if (renderable != NULL) {
        USG_deallocate(renderable);
    }
}

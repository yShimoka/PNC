#include "Engine/Rendering/Renderable.h"

USG_List _USG_RENDER_getRenderableList() {
    static USG_List renderableList = NULL;

    if (renderableList == NULL) {
        renderableList = USG_LIST_create();
    }

    return renderableList;
}

struct USG_Renderable* USG_RENDER_createSquarePrimitive(SDL_Color color, SDL_Rect size) {
    USG_List pRenderList = _USG_RENDER_getRenderableList();

    // Create the element.
    struct USG_Renderable* nextObj = (struct USG_Renderable *)malloc(sizeof(struct USG_Renderable));

    nextObj->type = USG_RENDER_PRIMITIVE_SQUARE;
    nextObj->dest = size;
    nextObj->color = color;

    // Append the new object.
    USG_LIST_append(pRenderList, nextObj);

    // Return the object.
    return nextObj;
}

struct USG_Renderable* USG_RENDER_createTexture(SDL_Texture* texture, struct USG_UVCoords source, SDL_Rect dest) {
    USG_List pRenderList = _USG_RENDER_getRenderableList();

    // Create the element.
    struct USG_Renderable* nextObj = (struct USG_Renderable *)malloc(sizeof(struct USG_Renderable));

    nextObj->type = USG_RENDER_TEXTURE;
    nextObj->pTexture = texture;
    nextObj->src = source;
    nextObj->dest = dest;

    // Append the new object.
    USG_LIST_append(pRenderList, nextObj);

    // Return the object.
    return nextObj;
}

void _USG_RENDER_clearElement(void* element) {
    struct USG_Renderable* renderable = element;
    if (renderable != NULL) {
        if (renderable->type == USG_RENDER_TEXTURE) {
            SDL_DestroyTexture(renderable->pTexture);
        }

        free(renderable);
    }
}

void USG_RENDER_clear() {
    // Loop through all the elements.
    USG_List list = _USG_RENDER_getRenderableList();

    USG_LIST_forEach(list, _USG_RENDER_clearElement);

    // Clear the list.
    USG_LIST_clear(list);
}

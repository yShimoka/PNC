#include "Engine/Core/GameObject.h"

#include "Engine/Tools/Allocator.h"
#include "Engine/Rendering/Layer.h"
#include "Engine/Fs/ImageLoader.h"
#include "Engine/Fs/FontLoader.h"

USG_List _USG_getGameObjects() {
    static USG_List list = NULL;

    if (list == NULL) {
        list = USG_LIST_create();
    }

    return list;
}

USG_GameObject USG_createSprite(const char * texturePath, struct USG_Rect uv, struct USG_Rect dest, const char * layer) {
    USG_GameObject object = (USG_GameObject)USG_allocate(sizeof(struct USG_GameObjectBase));

    object->renderable = USG_RENDER_createTexture(USG_IMG_loadFromFile(texturePath)->pTexture, uv, dest);
    USG_LAYER_addRenderable(layer, object->renderable);

    // TODO : Repair the masking.
    object->bIsMasked = 0;
    object->mask = NULL;
    // TODO : Implement transforms.
    object->transform = USG_DEFAULT_TRANSFORM;
    object->transform.origin = dest.origin;

    object->dest = dest;
    object->uvs = uv;

    object->update = NULL;

    USG_LIST_append(_USG_getGameObjects(), object);


    return object;
}

USG_GameObject USG_createSquare(SDL_Color color, struct USG_Rect dest, const char * layer) {
    USG_GameObject object = (USG_GameObject)USG_allocate(sizeof(struct USG_GameObjectBase));

    object->renderable = USG_RENDER_createSquarePrimitive(color, dest);
    USG_LAYER_addRenderable(layer, object->renderable);

    // TODO : Repair the masking.
    object->bIsMasked = 0;
    object->mask = NULL;
    // TODO : Implement transforms.
    object->transform = USG_DEFAULT_TRANSFORM;
    object->transform.origin = dest.origin;

    object->dest = dest;
    object->uvs = USG_RECT(0, 0, 1, 1);

    object->update = NULL;

    USG_LIST_append(_USG_getGameObjects(), object);


    return object;
}

USG_GameObject USG_createText(const char * text, const char * font, int fontSize, SDL_Color color, struct USG_Rect dest, const char * layer) {
    USG_GameObject object = (USG_GameObject)USG_allocate(sizeof(struct USG_GameObjectBase));

    object->renderable = USG_RENDER_createTexture(
        USG_FONT_render(text, USG_FONT_getFont(font, fontSize), color),
        USG_RECT(0, 0, 1, 1),
        dest
    );
    USG_LAYER_addRenderable(layer, object->renderable);

    // TODO : Repair the masking.
    object->bIsMasked = 0;
    object->mask = NULL;

    object->parent = NULL;

    object->transform = USG_DEFAULT_TRANSFORM;
    object->transform.origin = dest.origin;
    object->dest = dest;
    object->uvs = USG_RECT(0, 0, 1, 1);

    object->update = NULL;

    USG_LIST_append(_USG_getGameObjects(), object);


    return object;
}


void _USG_updateGameObject(void * element) {
    USG_GameObject gObj = (USG_GameObject)element;
    if (gObj->update != NULL) {
        gObj->update(gObj);
    }

    // Update the renderable.
    // Apply the transformations.
    struct USG_Vector size = gObj->dest.extent, position = gObj->dest.origin;
    USG_GameObject parent = gObj->parent;
    while (parent != NULL) {
        position = USG_V_reverseTransform(parent->transform, position);

        parent = parent->parent;
    }

    // Update the renderable.
    gObj->renderable->dest = USG_RECT_V(position, size);

    // TODO : Implement masking.
}

void USG_updateGameObjects() {
    USG_LIST_forEach(_USG_getGameObjects(), _USG_updateGameObject);
}

void USG_GO_setPosition(USG_GameObject object, struct USG_Vector pos) { object->transform.origin = pos; object->dest.origin = pos; }
void USG_GO_setSize(USG_GameObject object, struct USG_Vector size) { object->dest.extent = size; }
struct USG_Vector USG_GO_getPosition(USG_GameObject object) { return object->transform.origin; }
struct USG_Vector USG_GO_getSize(USG_GameObject object) { return object->dest.extent; }
void USG_GO_move(USG_GameObject object, struct USG_Vector delta) {
    USG_GO_setPosition(object,
        USG_V_add(USG_GO_getPosition(object), delta)
    );
}

void _USG_clearGameObject(void* element) {
    USG_GameObject gameObj = (USG_GameObject)element;

    USG_deallocate(gameObj);
}



void USG_clearGameObjects() {
    USG_LIST_forEach(_USG_getGameObjects(), _USG_clearGameObject);

    USG_LIST_clear(_USG_getGameObjects());
}
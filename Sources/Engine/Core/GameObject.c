#include "Engine/Core/GameObject.h"

#include "Engine/Tools/Allocator.h"
#include "Engine/Rendering/Layer.h"
#include "Engine/Fs/ImageLoader.h"
#include "Engine/Fs/FontLoader.h"

#include <stdio.h>

int gobjCounter = 0;

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

    object->parent = NULL;
    object->update = NULL;

    object->uid = ++gobjCounter;

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

    object->parent = NULL;
    object->update = NULL;

    object->uid = ++gobjCounter;

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

    object->parent = NULL;
    object->update = NULL;

    object->uid = ++gobjCounter;

    USG_LIST_append(_USG_getGameObjects(), object);


    return object;
}

struct USG_Rect USG_GO_getWorld(USG_GameObject object) {
    struct USG_Rect world = object->dest;
    USG_GameObject parent = object->parent;
    while (parent != NULL) {
        world.origin = USG_V_reverseTransform(parent->transform, world.origin);

        parent = parent->parent;
    }

    return world;
}

void _USG_updateGameObject(void * element) {
    USG_GameObject gObj = (USG_GameObject)element;
    if (gObj->update != NULL) {
        gObj->update(gObj);
    }

    // Update the renderable.
    // Apply the transformations.
    struct USG_Rect dest = USG_GO_getWorld(gObj);
    struct USG_Rect uv = gObj->uvs;

    // Check if the masking is enabled.
    if (gObj->bIsMasked && gObj->mask != NULL) {
        // Get the intersection of the square and its mask.
        struct USG_Rect inter = USG_R_intersect(dest, USG_GO_getWorld(gObj->mask));

        // Morph the uv map.
        //uv = USG_RECT_V(
        //    USG_V_sub(inter.origin, dest.origin),
        //    USG_V_sub(inter.extent, dest.extent)
        //);
        uv.origin = USG_V_sub(inter.origin,dest.origin);
        uv.extent = inter.extent;

        uv.origin.x /= dest.extent.x;
        uv.origin.y /= dest.extent.y;
        uv.extent.x /= dest.extent.x;
        uv.extent.y /= dest.extent.y;

        dest = inter;
    }

    // Update the renderable.
    gObj->renderable->dest = dest;
    gObj->renderable->src = uv;
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

void USG_destroy(USG_GameObject* object) {
    int dbg = USG_LIST_size(_USG_getGameObjects());
    int index = USG_LIST_find(_USG_getGameObjects(), *object);

    if (index >= 0) USG_LIST_remove(_USG_getGameObjects(), index);
    else fprintf(stderr, "GameObject does not exist !");
    
    dbg = USG_LIST_size(_USG_getGameObjects());

    USG_deallocate(*object);
    *object = NULL;
}

void _USG_clearGameObject(void* element) {
    USG_GameObject gameObj = (USG_GameObject)element;

    USG_deallocate(gameObj);
}



void USG_clearGameObjects() {
    USG_LIST_forEach(_USG_getGameObjects(), _USG_clearGameObject);

    USG_LIST_clear(_USG_getGameObjects());
}

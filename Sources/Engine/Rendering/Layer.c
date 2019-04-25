#include "Engine/Rendering/Layer.h"

#include "Engine/Tools/Allocator.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

USG_List _USG_LAYER_getLayerList() {
    static USG_List list = NULL;

    if (list == NULL) {
        list = USG_LIST_create();
    }

    return list;
}

int _USG_LAYER_comparer(void* a, void* b) {
    struct USG_Layer *la = (struct USG_Layer *)a, *lb = (struct USG_Layer *)b;

    if (la->zOrder < lb->zOrder) return 1;
    else if (la->zOrder > lb->zOrder) return -1;
    else return 0;
}

void USG_LAYER_make(const char * name, int zOrder) {
    // Check if the layer exists.
    struct USG_Node* head = USG_LIST_findFirst(*_USG_LAYER_getLayerList());

    while (
        (head != NULL) &&
        (strcmp((*(struct USG_Layer *)(head->pContents)).pName, name) != 0)
    ) head = head->pNext;

    if (head != NULL) {
        // Print the error.
        fprintf(stderr, "There already exists a layer named `%s`\n", name);
    } else {
        // Create the layer.
        struct USG_Layer * layer = (struct USG_Layer *)USG_allocate(1, sizeof(struct USG_Layer));

        layer->pName = name;
        layer->zOrder = zOrder;
        layer->pRenderables = USG_LIST_create();

        // Add it to the list.
        USG_LIST_append(_USG_LAYER_getLayerList(), layer);
        USG_LIST_sort(_USG_LAYER_getLayerList(), _USG_LAYER_comparer);
    }
}

void USG_LAYER_addRenderable(const char * name, struct USG_Renderable* renderable) {
    // Check if the layer exists.
    struct USG_Node* head = USG_LIST_findFirst(*_USG_LAYER_getLayerList());

    while (
        (head != NULL) &&
        (strcmp((*(struct USG_Layer *)(head->pContents)).pName, name) != 0)
    ) head = head->pNext;

    if (head == NULL) {
        // Print the error.
        fprintf(stderr, "No such layer %s\n", name);
    } else {
        struct USG_Layer * layer = (struct USG_Layer *)head->pContents;
        // Add the element to the layer.
        USG_LIST_append(layer->pRenderables, renderable);
        renderable->pLayer = layer;
    }
}

void USG_LAYER_destroyRenderable(struct USG_Renderable* renderable) {
    // Remove from the layer.
    struct USG_Layer *layer = renderable->pLayer;

    int index = USG_LIST_find(layer->pRenderables, renderable);

    if (index >= 0) USG_LIST_remove(layer->pRenderables, index);

    // Destroy the renderable.
    USG_deallocate(renderable);
}

void USG_LAYER_changeLayer(struct USG_Renderable* renderable, const char * newLayer) {
    // Check if the layer exists.
    struct USG_Node* head = USG_LIST_findFirst(*_USG_LAYER_getLayerList());

    while (
        (head != NULL) &&
        (strcmp((*(struct USG_Layer *)(head->pContents)).pName, newLayer) != 0)
    ) head = head->pNext;

    if (head == NULL) {
        // Print the error.
        fprintf(stderr, "No such layer %s\n", newLayer);
    } else {
        struct USG_Layer * layer = (struct USG_Layer *)head->pContents;

        // Remove it from the old layer.
        USG_LIST_remove(renderable->pLayer->pRenderables, USG_LIST_find(renderable->pLayer->pRenderables, renderable));

        // Add the element to the layer.
        renderable->pLayer = layer;
        USG_LIST_append(layer->pRenderables, renderable);

    }
}

void USG_LAYER_clearLayer(void* element) {
    struct USG_Layer *layer = (struct USG_Layer *)element;

    USG_LIST_forEach(layer->pRenderables, _USG_RENDER_clearElement);

    USG_LIST_clear(layer->pRenderables);

    USG_deallocate(layer);
}

void USG_LAYER_clear() {
    USG_LIST_forEach(_USG_LAYER_getLayerList(), USG_LAYER_clearLayer);

    USG_LIST_clear(_USG_LAYER_getLayerList());
}
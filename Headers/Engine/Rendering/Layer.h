#ifndef __USAGI_LAYER_H__
#define __USAGI_LAYER_H__

#include "Engine/Tools/List.h"
#include "Engine/Rendering/Renderable.h"

struct USG_Layer {
    const char * pName;

    USG_List pRenderables;

    int zOrder;
};

USG_List _USG_LAYER_getLayerList();
void USG_LAYER_make(const char * name, int zOrder);
void USG_LAYER_addRenderable(const char * name, struct USG_Renderable* renderable);
void USG_LAYER_destroyRenderable(struct USG_Renderable* renderable);
void USG_LAYER_changeLayer(struct USG_Renderable* renderable, const char * newLayer);
USG_List USG_LAYER_sortedRenderableList();

void USG_LAYER_clear();

#endif /* __USAGI_LAYER_H__ */
#ifndef __USAGI_GAMEOBJECT_H__
#define __USAGI_GAMEOBJECT_H__

#include <SDL2/SDL.h>

#include "Engine/Math/Rect.h"
#include "Engine/Math/Transform.h"
#include "Engine/Tools/List.h"
#include "Engine/Rendering/Renderable.h"

#define USG_COLOR(r, g, b, a) (SDL_Color) { r, g, b, a }

#define USG_ASSETS_PATH "Assets/"
#define USG_TEXTURE_PATH(file) USG_ASSETS_PATH  "Images/" file ".png"
#define USG_FONT_PATH(file) USG_ASSETS_PATH "Fonts/" file
#define USG_SOUND_PATH(file) USG_ASSETS_PATH "Sounds/" file

struct USG_GameObjectBase {
    int uid;

    struct USG_GameObjectBase *parent;

    struct USG_Transform transform;
    struct USG_Rect uvs;
    struct USG_Rect dest;
    struct USG_GameObjectBase *mask;

    struct USG_Renderable* renderable;

    void (*update)(struct USG_GameObjectBase *);

    int bIsMasked;
    int bIsVisible;
    int zOrder;
};

typedef struct USG_GameObjectBase * USG_GameObject;

USG_List _USG_getGameObjects();

USG_GameObject USG_createSprite(const char * texturePath, struct USG_Rect uv, struct USG_Rect dest, const char * layer, int zOrder);
USG_GameObject USG_createSquare(SDL_Color color, struct USG_Rect dest, const char * layer, int zOrder);
USG_GameObject USG_createText(const char * text, const char * font, int fontSize, SDL_Color color, struct USG_Rect dest, const char * layer, int zOrder);

void USG_GO_setPosition(USG_GameObject object, struct USG_Vector pos);
void USG_GO_setSize(USG_GameObject object, struct USG_Vector size);
struct USG_Vector USG_GO_getPosition(USG_GameObject object);
struct USG_Vector USG_GO_getWorldPosition(USG_GameObject object);
struct USG_Vector USG_GO_getSize(USG_GameObject object);
void USG_GO_move(USG_GameObject object, struct USG_Vector delta);

void USG_changeLayer(USG_GameObject object, const char * newLayer);

void USG_destroy(USG_GameObject* object);

void USG_updateGameObjects();

void USG_clearGameObjects();

#endif /* __USAGI_GAMEOBJECT_H__ */
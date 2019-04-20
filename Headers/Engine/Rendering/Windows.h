#ifndef __USAGI_WINDOW_H__
#define __USAGI_WINDOW_H__

#include <SDL2/SDL.h>

#include "Engine/Rendering/Renderable.h"

// Main window object.
typedef struct {
    int width;
    int height;

    int x;
    int y;

    const char * pName;

    uint32_t flags;

    SDL_Window* pWindow;
    SDL_Renderer* pRenderer;
} USG_Window;

// Window manager methods.

USG_Window* _USG_WINMAN_getWindow();

void USG_WINMAN_render(void* element);

void USG_WINMAN_init();

void USG_WINMAN_quit();

void USG_WINMAN_setWindowParams(const char * title, int x, int y, int width, int height, uint32_t flags);

void USG_WINMAN_present();

#endif /* __USAGI_WINDOW_H__ */
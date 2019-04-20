#include "Engine/Rendering/Windows.h"

USG_Window* _USG_WINMAN_getWindow() {
    static USG_Window windowInstance;

    return &windowInstance;
}

void USG_WINMAN_render(void* element) {
    struct USG_Renderable* renderable = (struct USG_Renderable*)element;
    USG_Window* pWindow = _USG_WINMAN_getWindow();

    // Check the render type.
    if (renderable->type == USG_RENDER_PRIMITIVE_SQUARE) {
        // Render a square.
        SDL_SetRenderDrawColor(pWindow->pRenderer, renderable->color.r, renderable->color.g, renderable->color.b, renderable->color.a);
        SDL_RenderFillRect(pWindow->pRenderer, &(renderable->dest));
    } else if (renderable->type == USG_RENDER_TEXTURE) {
        // Compute the UV coordinates.
        uint32_t format; int access, w, h;
        SDL_QueryTexture(renderable->pTexture, &format, &access, &w, &h);
        SDL_Rect UV;
        UV.x = renderable->src.x * w;
        UV.w = renderable->src.w * w;
        UV.y = renderable->src.y * h;
        UV.h = renderable->src.h * h;

        // Render the texture.
        SDL_RenderCopy(pWindow->pRenderer, renderable->pTexture, &(UV), &(renderable->dest));
    }
}

void USG_WINMAN_init() {
    USG_Window* pWindow = _USG_WINMAN_getWindow();

    // Create the window.
    pWindow->pWindow = SDL_CreateWindow(pWindow->pName, pWindow->x, pWindow->y, pWindow->width, pWindow->height, pWindow->flags);

    // Create the renderer.
    pWindow->pRenderer = SDL_CreateRenderer(pWindow->pWindow, -1, 0);

}

void USG_WINMAN_quit() {
    USG_Window* pWindow = _USG_WINMAN_getWindow();

    // Clear the renderable list.
    USG_RENDER_clear();

    // Destroy the renderer.
    SDL_DestroyRenderer(pWindow->pRenderer);

    // Destroy the window.
    SDL_DestroyWindow(pWindow->pWindow);
}

void USG_WINMAN_setWindowParams(const char * title, int x, int y, int width, int height, uint32_t flags) {
    USG_Window* pWindow = _USG_WINMAN_getWindow();

    pWindow->pName = title;
    pWindow->x = x;
    pWindow->y = y;
    pWindow->width = width;
    pWindow->height = height;
    pWindow->flags = flags;    
}

void USG_WINMAN_present() {
    USG_LIST_forEach(_USG_RENDER_getRenderableList(), USG_WINMAN_render);

    USG_Window* pWindow = _USG_WINMAN_getWindow();

    SDL_RenderPresent(pWindow->pRenderer);
    SDL_SetRenderDrawColor(pWindow->pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(pWindow->pRenderer);
}
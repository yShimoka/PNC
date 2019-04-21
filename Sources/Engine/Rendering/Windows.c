#include "Engine/Rendering/Windows.h"
#include "Engine/Rendering/Layer.h"
#include "Engine/Fs/FontLoader.h"
#include "Engine/Fs/ImageLoader.h"
#include "Engine/Fs/SoundLoader.h"

USG_Window* _USG_WINMAN_getWindow() {
    static USG_Window windowInstance;

    return &windowInstance;
}

void USG_WINMAN_render(void* element) {
    struct USG_Renderable* renderable = (struct USG_Renderable*)element;

    if (!renderable->bVisible) return;

    USG_Window* pWindow = _USG_WINMAN_getWindow();
    // Check the render type.
    if (renderable->type == USG_RENDER_PRIMITIVE_SQUARE) {
        // Render a square.
        SDL_SetRenderDrawColor(pWindow->pRenderer, renderable->color.r, renderable->color.g, renderable->color.b, renderable->color.a);
        SDL_RenderFillRect(pWindow->pRenderer, &USG_R_SDL(renderable->dest));
    } else if (renderable->type == USG_RENDER_TEXTURE) {
        // Compute the UV coordinates.
        uint32_t format; int access, w, h;
        SDL_QueryTexture(renderable->pTexture, &format, &access, &w, &h);
        struct USG_Rect uv = USG_R_mul(renderable->src, USG_VECTOR(w, h));

        SDL_Rect sdlSrc = USG_R_SDL(uv);
        SDL_Rect sdlDst = USG_R_SDL(renderable->dest);

        // Render the texture.
        SDL_RenderCopy(pWindow->pRenderer, renderable->pTexture, &(sdlSrc), &(sdlDst));
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
    USG_LAYER_clear();

    // Clear any loadded assets.
    USG_FONT_clear();
    USG_MIX_clear();
    USG_IMG_clear();

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

void _USG_WINMAN_renderLayer(void* element) {
    struct USG_Layer *layer = (struct USG_Layer *)element;

    USG_LIST_forEach(layer->pRenderables, USG_WINMAN_render);
}

void USG_WINMAN_present() {
    USG_LIST_forEach(_USG_LAYER_getLayerList(), _USG_WINMAN_renderLayer);

    USG_Window* pWindow = _USG_WINMAN_getWindow();

    SDL_RenderPresent(pWindow->pRenderer);
    SDL_SetRenderDrawColor(pWindow->pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(pWindow->pRenderer);
}
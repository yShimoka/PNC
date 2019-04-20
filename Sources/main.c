#include "Engine/Rendering/Windows.h"
#include "Engine/Rendering/Renderable.h"
#include "Engine/Fs/ImageLoader.h"
#include "Engine/Fs/FontLoader.h"

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    TTF_Init();

    USG_WINMAN_setWindowParams("Point N Click", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

    USG_WINMAN_init();

    USG_Window* pWindow = _USG_WINMAN_getWindow();
    SDL_SetRenderDrawColor(pWindow->pRenderer, 255, 0, 0, 255);

    struct USG_Renderable* simpleSquare1 = USG_RENDER_createSquarePrimitive((SDL_Color){255, 255, 255, 255}, (SDL_Rect){0, 0, 25, 25});
    struct USG_Renderable* sampletexture = USG_RENDER_createTexture(USG_IMG_loadFromFile("Assets/Images/UVTextureChecker.png"), (struct USG_UVCoords){0.5, 0.8, 0.1, 0.1}, (SDL_Rect){100, 100, 400, 400});
    
    struct USG_Font* fontA = USG_FONT_getFont("Assets/Fonts/Ubuntu.ttf", 32);
    struct USG_Font* fontB = USG_FONT_getFont("Assets/Fonts/Ubuntu.ttf", 32);
    struct USG_Renderable* sampletext = USG_RENDER_createTexture(USG_FONT_render("Hello, World!", USG_FONT_getFont("Assets/Fonts/Ubuntu.ttf", 32), (SDL_Color){255, 255, 255, 255}, (SDL_Color){0, 0, 0, 0}), (struct USG_UVCoords){0, 0, 1, 1}, (SDL_Rect) {0, 150, 100, 25});
    
    int stop = 0;
    while (!stop) {
        SDL_Event ev;
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) {
                stop = 1;
            }
        }
        USG_WINMAN_present();
    }


    USG_WINMAN_quit();

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
#include "Engine/Rendering/Windows.h"
#include "Engine/Rendering/Renderable.h"
#include "Engine/Rendering/Layer.h"
#include "Engine/Fs/ImageLoader.h"
#include "Engine/Fs/FontLoader.h"
#include "Engine/Fs/SoundLoader.h"
#include "Engine/Math/Transform.h"
#include "Engine/Math/Vector.h"

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>

int main(int argv, char * argc[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    TTF_Init();
    Mix_Init(0);

    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

    USG_WINMAN_setWindowParams("Point N Click", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

    USG_WINMAN_init();

    USG_Window* pWindow = _USG_WINMAN_getWindow();
    SDL_SetRenderDrawColor(pWindow->pRenderer, 255, 0, 0, 255);

    USG_LAYER_make("Text", 3);
    USG_LAYER_make("Front-End", 2);
    USG_LAYER_make("Back-End", 1);
    
    struct USG_Renderable* main = USG_RENDER_createSquarePrimitive(
        (SDL_Color) { 255, 255, 255, 255 },
        (SDL_Rect) { 50, 50, 500, 500 }
    );
    USG_LAYER_addRenderable("Front-End", main);
    
    struct USG_Renderable* child = USG_RENDER_createSquarePrimitive(
        (SDL_Color) { 0, 0, 255, 255 },
        (SDL_Rect) { 0, 0, 50, 50 }
    );
    USG_LAYER_addRenderable("Back-End", child);

    struct USG_Renderable* child2 = USG_RENDER_createTexture(
        USG_IMG_loadFromFile("Assets/Images/UVTextureChecker.png")->pTexture,
        (struct USG_UVCoords) { 0.5, 0.5, 0.1, 0.1 },
        (SDL_Rect) { 0, 0, 50, 50 }
    );
    USG_LAYER_addRenderable("Back-End", child2);

    struct USG_Renderable* windowTitle = USG_RENDER_createTexture(
        USG_FONT_render(
            "Hello, World !", 
            USG_FONT_getFont("Assets/Fonts/VCR_OSD.ttf", 72),
            (SDL_Color) { 0, 0, 0, 255 },
            (SDL_Color) { 0, 0, 255, 255 }
        ),
        (struct USG_UVCoords) {0, 0, 1, 1},
        (SDL_Rect) { 0, 0, 400, 50 }
    );
    USG_LAYER_addRenderable("Text", windowTitle);

    struct USG_Transform mainT = { NULL, (struct USG_Vector) { 50, 50 }, 1, 2 };
    struct USG_Vector childRel = { 0, 0 }; 
    struct USG_Vector titleRel = { 25, 25 }; 

    int stop = 0;
    int grab = 0;
    while (!stop) {
        uint32_t start = SDL_GetTicks();

        childRel.x -= 0.1f;
        childRel.y -= 0.2f;

        child->dest.x = USG_V_reverseTransform(mainT, childRel).x;
        child->dest.y = USG_V_reverseTransform(mainT, childRel).y;

        windowTitle->dest.x = USG_V_reverseTransform(mainT, titleRel).x;
        windowTitle->dest.y = USG_V_reverseTransform(mainT, titleRel).y;

        main->dest.x = mainT.origin.x;
        main->dest.y = mainT.origin.y;

        SDL_Event ev;
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) {
                stop = 1;
            } else if (ev.type == SDL_MOUSEBUTTONDOWN) {
                grab = 1;
            } else if (ev.type == SDL_MOUSEBUTTONUP) {
                grab = 0;
            } else if (ev.type == SDL_MOUSEMOTION) {
                if (grab) {
                    mainT.origin.x += ev.motion.xrel;
                    mainT.origin.y += ev.motion.yrel;
                }
            }
        }
        USG_WINMAN_present();

        uint32_t total = SDL_GetTicks() - start;
        if (total < 16) {
            SDL_Delay(16 - total);
        }
    }


    USG_WINMAN_quit();

    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}

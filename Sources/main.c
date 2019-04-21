#include "Engine/Rendering/Windows.h"
#include "Engine/Core/GameObject.h"
#include "Engine/Rendering/Layer.h"

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
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

    USG_LAYER_make("Desktop", -1);
    USG_LAYER_make("Base", 0);
    USG_LAYER_make("Front", 1);

    USG_GameObject desktop = USG_createSquare(USG_COLOR(0,120,127,255), USG_RECT(0, 0, 800, 600), "Desktop");
    USG_GameObject windowFrame = USG_createSquare(USG_COLOR(0,0,0,255), USG_RECT(0, 0, 300, 200), "Base");
    USG_GameObject windowTitleBar = USG_createSquare(USG_COLOR(0,0,200,255), USG_RECT(1, 1, 298, 25), "Base");
    windowTitleBar->parent = windowFrame;
    USG_GameObject windowTitle = USG_createText("Find the virus !", "Assets/Fonts/VCR_OSD.ttf", 72, USG_COLOR(255, 255, 255, 255), USG_RECT(5, 5, 150, 15), "Base");
    windowTitle->parent = windowTitleBar;
    USG_GameObject windowContents = USG_createSquare(USG_COLOR(191,184,191,255), USG_RECT(1, 27, 298, 172), "Base");
    windowContents->parent = windowFrame;

    USG_GameObject windowCross = USG_createSprite("Assets/Images/Close.png", USG_RECT_UNIT, USG_RECT(270, 2, 26, 26), "Base");
    windowCross->parent = windowTitleBar;

    USG_GameObject virus = USG_createSprite("Assets/Images/Virus.png", USG_RECT_UNIT, USG_RECT(500, 300, 50, 50), "Front");
    virus->bIsMasked = 1;
    virus->mask = windowContents;

    int stop = 0;
    int grab = 0;
    while (!stop) {
        uint32_t start = SDL_GetTicks();

        SDL_Event ev;
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) {
                stop = 1;
            } else if (ev.type == SDL_MOUSEBUTTONDOWN) {
                grab = 1;
            } else if (ev.type == SDL_MOUSEBUTTONUP) {
                grab = 0;
            } else if (ev.type == SDL_MOUSEMOTION && grab) {
                USG_GO_move(windowFrame, USG_VECTOR(ev.motion.xrel, ev.motion.yrel));
            }
        }

        USG_updateGameObjects();
        USG_WINMAN_present();

        uint32_t total = SDL_GetTicks() - start;
        if (total < 16) {
            SDL_Delay(16 - total);
        }
    }

    USG_clearGameObjects();
    USG_WINMAN_quit();

    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}

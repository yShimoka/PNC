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

    USG_LAYER_make("Base", 0);
    USG_LAYER_make("Front", 1);
    
    USG_GameObject main = USG_createSquare(USG_COLOR(255, 255, 255, 255), USG_RECT(300, 200, 200, 200), "Base");

    USG_GameObject child = USG_createSquare(USG_COLOR(128, 26, 26, 255), USG_RECT(50, 50, 100, 100), "Front");
    child->parent = main;

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
                USG_GO_move(main, USG_VECTOR(ev.motion.xrel, ev.motion.yrel));
                USG_GO_move(child, USG_VECTOR(ev.motion.xrel, ev.motion.yrel));
            }
        }

        USG_updateGameObjects();
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

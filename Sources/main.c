#include "Engine/Rendering/Windows.h"
#include "Engine/Core/GameObject.h"
#include "Engine/Rendering/Layer.h"
#include "Game/Windows/VirtualWindow.h"
#include "Game/Windows/Console.h"
#include "Engine/Fs/FontLoader.h"

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>

// DEBUG : Prints a text in the window.
void consoleEvent(void * element, SDL_Event * event) {
    USG_Console console = element;

    if (event->type == SDL_MOUSEBUTTONDOWN) {
        USG_CON_print(console, "Wildcard Wombat");
    }
}

int main(int argv, char * argc[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    TTF_Init();
    Mix_Init(0);

    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

    USG_WINMAN_setWindowParams("Point N Click", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

    USG_WINMAN_init();

    USG_Window* pWindow = _USG_WINMAN_getWindow();

    USG_LAYER_make("Desktop-Back", 0);
    USG_LAYER_make("Desktop-Front", 1);

    USG_Console console = USG_CON_createConsole("?????????");
    USG_GO_setPosition(console->window->frame, USG_VECTOR(400, 200));
    console->window->child_onEvent = consoleEvent;
    
    USG_GameObject desktop = USG_createSquare(USG_COLOR(0, 127, 0, 255), USG_RECT(0, 0, 800, 600), "Desktop-Back", 0);

    int stop = 0;
    int grab = 0;
    while (!stop) {
        uint32_t start = SDL_GetTicks();

        SDL_Event ev;
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) {
                stop = 1;
            }

            USG_VWIN_onEvent(ev);
        }

        USG_VWIN_onUpdate();
        USG_updateGameObjects();
        USG_WINMAN_present();

        uint32_t total = SDL_GetTicks() - start;
        if (total < 16) {
            SDL_Delay(16 - total);
        }
    }

    USG_VWIN_clear();
    USG_clearGameObjects();
    USG_WINMAN_quit();

    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}

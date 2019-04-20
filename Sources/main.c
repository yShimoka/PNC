#include "Engine/Rendering/Windows.h"
#include "Engine/Rendering/Renderable.h"
#include "Engine/Fs/ImageLoader.h"
#include "Engine/Fs/FontLoader.h"
#include "Engine/Fs/SoundLoader.h"

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

    struct USG_Renderable* simpleSquare1 = USG_RENDER_createSquarePrimitive((SDL_Color){255, 255, 255, 255}, (SDL_Rect){0, 0, 25, 25});
    struct USG_Renderable* sampletexture = USG_RENDER_createTexture(USG_IMG_loadFromFile("Assets/Images/UVTextureChecker.png"), (struct USG_UVCoords){0.5, 0.8, 0.1, 0.1}, (SDL_Rect){100, 100, 400, 400});

    struct USG_Font* fontA = USG_FONT_getFont("Assets/Fonts/Ubuntu.ttf", 32);
    struct USG_Font* fontB = USG_FONT_getFont("Assets/Fonts/Ubuntu.ttf", 32);
    struct USG_Renderable* sampletext = USG_RENDER_createTexture(USG_FONT_render("Hello, World!", USG_FONT_getFont("Assets/Fonts/Ubuntu.ttf", 32), (SDL_Color){255, 255, 255, 255}, (SDL_Color){0, 0, 0, 0}), (struct USG_UVCoords){0, 0, 1, 1}, (SDL_Rect) {0, 150, 100, 25});

    struct USG_Sfx* sfx = USG_MIX_loadSFX("Assets/Sounds/beep-07.wav");
    Mix_VolumeChunk(sfx->pSoundChunck, 128);

    int stop = 0;
    while (!stop) {
        uint32_t start = SDL_GetTicks();

        SDL_Event ev;
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) {
                stop = 1;
            } else if (ev.type == SDL_KEYDOWN) {
                if (ev.key.keysym.sym == SDLK_SPACE) {
                    Mix_PlayChannel(-1, sfx->pSoundChunck, 0);
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

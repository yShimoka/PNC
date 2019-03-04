#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>

#define SCREEN_WIDTH 1680
#define SCREEN_HEIGHT 1050
#define WINDOW_WIDTH 100
#define WINDOW_HEIGHT 100

#define WINDOW_COUNT_WIDTH SCREEN_WIDTH/WINDOW_WIDTH
#define WINDOW_COUNT_HEIGHT SCREEN_HEIGHT/WINDOW_HEIGHT

int counter = 0;
typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* rendered;
    int id;
    int timer;
} WindowMgr;

void addWindow(WindowMgr** managers, SDL_Surface* rendered) {
    // Create a new window object.
    WindowMgr mgr = { NULL, NULL, NULL, counter++, 0 };

    // Create a SDL window.
    mgr.window = SDL_CreateWindow(
        "Window",
        (mgr.id % WINDOW_COUNT_WIDTH) * WINDOW_WIDTH,
        (mgr.id / WINDOW_COUNT_WIDTH) * WINDOW_HEIGHT,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    mgr.renderer = SDL_CreateRenderer(mgr.window, -1, 0);
    mgr.rendered = SDL_CreateTextureFromSurface(mgr.renderer, rendered);

    // Resize the managers array.
    (*managers) = realloc((*managers), sizeof(WindowMgr) * (counter));
    (*managers)[counter - 1] = mgr;
}

void renderWindows(WindowMgr* managers) {
    for (int i = 0; i < counter; i++) {
        SDL_RenderClear(managers[i].renderer);
        SDL_RenderCopy(managers[i].renderer, managers[i].rendered, NULL, NULL);
        SDL_RenderPresent(managers[i].renderer);
    }
}

void destroyWindows(WindowMgr* managers) {
    for (int i = 0; i < counter; i++) {
        SDL_DestroyTexture(managers[i].rendered);
        SDL_DestroyRenderer(managers[i].renderer);
        SDL_DestroyWindow(managers[i].window);
    }
}


int main(int argc, char * argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    WindowMgr* mgrList = NULL;

    TTF_Font* font = TTF_OpenFont("Assets/Fonts/Ubuntu.ttf", 54);
    SDL_Surface* txtSurf = TTF_RenderText_Solid(font, "Hello, World!", (SDL_Color){255, 255, 255});
    addWindow(&mgrList, txtSurf);

    int fpsCnt = 0;
    float fpsAvg[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    
    SDL_Event ev;
    int cont = 1;
    while (cont == 1) {
        Uint32 start = SDL_GetTicks();
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) {
                cont = 0;
            }
            else if (ev.type == SDL_KEYDOWN) {
                if(ev.key.keysym.sym == SDLK_SPACE) {
                    addWindow(&mgrList, txtSurf);
                }
            }
        }
        renderWindows(mgrList);
        Uint32 end = SDL_GetTicks();

        fpsCnt = (fpsCnt + 1) % 10;
        fpsAvg[fpsCnt] = 1000.0f / (end - start);

        float avg = 0.0f;
        for (int i = 0; i < 10; i++) {
            avg += fpsAvg[i];
        }
        printf("Windows: %d, FPS (average): %f\n", counter, avg / 10.0f);
    }

    destroyWindows(mgrList);
    free(mgrList);
    SDL_FreeSurface(txtSurf);
    TTF_Quit();
    SDL_Quit();

}
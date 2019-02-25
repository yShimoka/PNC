#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>

int main(int argc, char * argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow(
        "Hello, World!", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    TTF_Font* font = TTF_OpenFont("Assets/Fonts/Ubuntu.ttf", 54);
    SDL_Surface* txtSurf = TTF_RenderText_Solid(font, "Hello, World!", (SDL_Color){255, 255, 255});
    SDL_Texture* txtText = SDL_CreateTextureFromSurface(renderer, txtSurf);
    SDL_FreeSurface(txtSurf);

    
    SDL_Event ev;
    int cont = 1;
    while (cont == 1) {
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) {
                cont = 0;
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, txtText, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(txtText);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

}
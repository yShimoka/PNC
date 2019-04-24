#include "Engine/Rendering/Windows.h"
#include "Engine/Core/GameObject.h"
#include "Engine/Rendering/Layer.h"
#include "Game/CreationComposantsBasiques.h"

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

    InitLayers();





    InitDesktop(&desktop,&taskBarFrame,&taskBarStartButtonContour,&taskBarStartButtonFrame,&taskBarStartButtonTitle,&taskBarStartButtonLogo);

    InitConsole(&consoleFrame,&consoleTitleBar,&consoleTitleBarLogo,&consoleTitleBarText,&consoleContent,&consoleCross);



    USG_GameObject test = USG_createSquare(USG_COLOR(255, 255, 255, 255), USG_RECT(0, 0, 800, 600), "Desktop");
    USG_destroy(&test);

    // A RANGER DANS DES METHODES !!!!
    //test �criture console
    USG_GameObject ConsoleText = USG_createText("Bonjour, je suis un virus. Je vais te", "Assets/Fonts/VCR_OSD.ttf", 72, USG_COLOR(255, 248, 255, 255), USG_RECT(5, 5, 270, 15), "Base");
    ConsoleText->parent = consoleContent;

    USG_GameObject ConsoleText1 = USG_createText("tester ! Si tu est trop faible, je", "Assets/Fonts/VCR_OSD.ttf", 72, USG_COLOR(255, 248, 255, 255), USG_RECT(5, 25, 260, 15), "Base");
    ConsoleText1->parent = consoleContent;

    USG_GameObject ConsoleText2 = USG_createText("détruirai toutes tes données.", "Assets/Fonts/VCR_OSD.ttf", 72, USG_COLOR(255, 248, 255, 255), USG_RECT(5, 45, 220, 15), "Base");
    ConsoleText2->parent = consoleContent;

    USG_GameObject ConsoleText3 = USG_createText("Commençons donne-moi...", "Assets/Fonts/VCR_OSD.ttf", 72, USG_COLOR(255, 248, 255, 255), USG_RECT(5, 65, 220, 15), "Base");
    ConsoleText3->parent = consoleContent;

    InitGiveMe(&giveMeFrame,&giveMeTitleBar,&giveMeTitleBarLogo,&giveMeTitleBarText,&giveMeContent,&giveMeCross);

    USG_GameObject giveMeText = USG_createText("Une balle", "Assets/Fonts/VCR_OSD.ttf", 72, USG_COLOR(0, 0, 0, 255), USG_RECT(115, 100, 75, 15), "Front");
    giveMeText->parent = NULL;
    giveMeText->bIsMasked = 1;
    giveMeText->mask = giveMeContent;

    USG_GameObject Ball = USG_createSprite("Assets/Images/Ball.png", USG_RECT_UNIT, USG_RECT(10, 500, 20, 26), "Front");
    Ball->parent = NULL;

    USG_GameObject ballText = USG_createText("balle", "Assets/Fonts/VCR_OSD.ttf", 72, USG_COLOR(255, 248, 255, 255), USG_RECT(0, 30, 25, 15), "Front");
    ballText->parent = Ball;

    /* Ajout d'un objet cach�
    USG_GameObject virus = USG_createSprite("Assets/Images/Virus.png", USG_RECT_UNIT, USG_RECT(500, 300, 50, 50), "Front");
    virus->parent = NULL;

    virus->bIsMasked = 1;
    virus->mask = windowContents;
    */
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
                //Gestion grab sur une fen�tre ATTENTION comme je cr�e les fen�tres dans des m�thodes sans utiliser de pointeur, je n'y est plus acc�s
                USG_GO_move(giveMeFrame, USG_VECTOR(ev.motion.xrel, ev.motion.yrel));
                USG_GO_move(Ball, USG_VECTOR(ev.motion.xrel, ev.motion.yrel));
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

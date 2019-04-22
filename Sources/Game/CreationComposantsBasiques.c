#include "Game/CreationComposantsBasiques.h"


void InitLayers(){
    //Création des layers de base
    USG_LAYER_make("Desktop", -1);
    USG_LAYER_make("Base", 0);
    USG_LAYER_make("Front", 1);
}

void InitDesktop(USG_GameObject *desktop, USG_GameObject *taskBarFrame, USG_GameObject *taskBarStartButtonContour, USG_GameObject *taskBarStartButtonFrame, USG_GameObject *taskBarStartButtonTitle, USG_GameObject *taskBarStartButtonLogo) {
    //Création du bureau
    *desktop = USG_createSquare(USG_COLOR(0,120,127,255), USG_RECT(0, 0, 800, 600), "Desktop");
    (*desktop)->parent = NULL;

    //Création de la barre des tâches
    *taskBarFrame = USG_createSquare(USG_COLOR(191,190,191,255),USG_RECT(0,570,800,600),"Desktop");
    (*taskBarFrame)->parent = NULL;

    //Création du bouton démarrer
    *taskBarStartButtonContour = USG_createSquare(USG_COLOR(0,0,0,255),USG_RECT(3,3,60,25),"Desktop");
    (*taskBarStartButtonContour)->parent = *taskBarFrame;
    //Fond gris
    *taskBarStartButtonFrame = USG_createSquare(USG_COLOR(191,190,191,255),USG_RECT(1,1,58,23),"Desktop");
    (*taskBarStartButtonFrame)->parent = *taskBarStartButtonContour;
    //TEXT
    *taskBarStartButtonTitle = USG_createText("Start", "Assets/Fonts/VCR_OSD.ttf", 72, USG_COLOR(0, 0, 0, 255), USG_RECT(25, 5, 30, 12), "Desktop");
    (*taskBarStartButtonTitle)->parent = *taskBarStartButtonFrame;
    //Logo
    *taskBarStartButtonLogo = USG_createSprite("Assets/Images/W95.png", USG_RECT_UNIT, USG_RECT(5, 3, 18, 18), "Desktop");
    (*taskBarStartButtonLogo)->parent = *taskBarStartButtonFrame;
}


void InitConsole(USG_GameObject *windowFrame, USG_GameObject *windowTitleBar, USG_GameObject *windowTitleBarLogo, USG_GameObject *windowTitleBarText, USG_GameObject *windowContent, USG_GameObject *windowCross) {
    //Création de la fenêtre console
    //FOND
    *windowFrame = USG_createSquare(USG_COLOR(191,190,191,255), USG_RECT(450, 5, 300, 200), "Base");
    (*windowFrame)->parent = NULL;
    //Barre Titre
    *windowTitleBar = USG_createSquare(USG_COLOR(0,0,127,255), USG_RECT(2, 2, 296, 25), "Base");
    (*windowTitleBar)->parent = *windowFrame;
    //LOGO Titre
    *windowTitleBarLogo = USG_createSprite("Assets/Images/Masked.png", USG_RECT_UNIT, USG_RECT(5, 5, 15, 15), "Base");
    (*windowTitleBarLogo)->parent = *windowTitleBar;
    //Titre Text
    *windowTitleBarText = USG_createText("Virus", "Assets/Fonts/VCR_OSD.ttf", 72, USG_COLOR(255, 248, 255, 255), USG_RECT(25, 7, 35, 10), "Base");
    (*windowTitleBarText)->parent = *windowTitleBar;
    //Contenu de la console
    *windowContent = USG_createSquare(USG_COLOR(0,0,0,255), USG_RECT(2, 30, 296, 168), "Base");
    (*windowContent)->parent = *windowFrame;
    //Croix pour quitter
    *windowCross = USG_createSprite("Assets/Images/ExitGriser.png", USG_RECT_UNIT, USG_RECT(275, 3, 20, 20), "Base");
    (*windowCross)->parent = *windowTitleBar;

}

void InitGiveMe(USG_GameObject *windowFrame, USG_GameObject *windowTitleBar, USG_GameObject *windowTitleBarLogo, USG_GameObject *windowTitleBarText, USG_GameObject *windowContent, USG_GameObject *windowCross) {
    //Création de la fenêtre console
    //FOND
    *windowFrame = USG_createSquare(USG_COLOR(191,190,191,255), USG_RECT(10, 5, 300, 200), "Base");
    (*windowFrame)->parent = NULL;
    //Barre Titre
    *windowTitleBar = USG_createSquare(USG_COLOR(0,0,127,255), USG_RECT(2, 2, 296, 25), "Base");
    (*windowTitleBar)->parent = *windowFrame;
    //LOGO Titre
    *windowTitleBarLogo = USG_createSprite("Assets/Images/Masked.png", USG_RECT_UNIT, USG_RECT(5, 5, 15, 15), "Base");
    (*windowTitleBarLogo)->parent = *windowTitleBar;
    //Titre Text
    *windowTitleBarText = USG_createText("Donne-moi", "Assets/Fonts/VCR_OSD.ttf", 72, USG_COLOR(255, 248, 255, 255), USG_RECT(25, 7, 70, 10), "Base");
    (*windowTitleBarText)->parent = *windowTitleBar;
    //Contenu de la console
    *windowContent = USG_createSquare(USG_COLOR(255,255,255,255), USG_RECT(2, 30, 296, 168), "Base");
    (*windowContent)->parent = *windowFrame;
    //Croix pour quitter
    *windowCross = USG_createSprite("Assets/Images/ExitGriser.png", USG_RECT_UNIT, USG_RECT(275, 3, 20, 20), "Base");
    (*windowCross)->parent = *windowTitleBar;

}

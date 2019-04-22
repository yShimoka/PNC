#ifndef CREATIONCOMPOSANTSBASIQUES_H_INCLUDED
#define CREATIONCOMPOSANTSBASIQUES_H_INCLUDED


#include "Engine/Core/GameObject.h"

USG_GameObject desktop;
USG_GameObject taskBarFrame;
USG_GameObject taskBarStartButtonContour;
USG_GameObject taskBarStartButtonFrame;
USG_GameObject taskBarStartButtonTitle;
USG_GameObject taskBarStartButtonLogo;

USG_GameObject consoleFrame;
USG_GameObject consoleTitleBar;
USG_GameObject consoleTitleBarLogo;
USG_GameObject consoleTitleBarText;
USG_GameObject consoleContent;
USG_GameObject consoleCross;

USG_GameObject giveMeFrame;
USG_GameObject giveMeTitleBar;
USG_GameObject giveMeTitleBarLogo;
USG_GameObject giveMeTitleBarText;
USG_GameObject giveMeContent;
USG_GameObject giveMeCross;

void InitLayers();
void InitDesktop(USG_GameObject *desktop, USG_GameObject *taskBarFrame, USG_GameObject *taskBarStartButtonContour, USG_GameObject *taskBarStartButtonFrame, USG_GameObject *taskBarStartButtonTitle, USG_GameObject *taskBarStartButtonLogo);
void InitConsole(USG_GameObject *windowFrame, USG_GameObject *windowTitleBar, USG_GameObject *windowTitleBarLogo, USG_GameObject *windowTitleBarText, USG_GameObject *windowContent, USG_GameObject *windowCross) ;
void InitGiveMe(USG_GameObject *windowFrame, USG_GameObject *windowTitleBar, USG_GameObject *windowTitleBarLogo, USG_GameObject *windowTitleBarText, USG_GameObject *windowContent, USG_GameObject *windowCross) ;

#endif // CREATIONCOMPOSANTSBASIQUES_H_INCLUDED

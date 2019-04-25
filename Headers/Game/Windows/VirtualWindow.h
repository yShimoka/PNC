#ifndef __VIRTUALWINDOW_H__
#define __VIRTUALWINDOW_H__

#include "Engine/Core/GameObject.h"

#define USG_VWIN_COLOR_WINDOW_BG       USG_COLOR(191, 190, 191, 255)
#define USG_VWIN_COLOR_WINDOW_CONTENTS USG_COLOR(222, 222, 222, 255)
#define USG_VWIN_COLOR_WINDOW_TITLEBAR USG_COLOR(  0,   0, 127, 255)
#define USG_VWIN_COLOR_WINDOW_TITLEBAR USG_COLOR(  0,   0, 127, 255)
#define USG_VWIN_COLOR_WINDOW_TITLETXT USG_COLOR(255, 248, 255, 255)

#define USG_VWIN_PATH_TITLETXT USG_FONT_PATH("VCR_OSD.ttf")
#define USG_VWIN_PATH_CROSS    USG_TEXTURE_PATH("ExitGriser")


#define USG_VWIN_MARGIN 2
#define USG_VWIN_LOGO_MARGIN 5
#define USG_VWIN_LOGOSIZE 15
#define USG_VWIN_TITLEHEIGHT (2 * USG_VWIN_LOGO_MARGIN + USG_VWIN_LOGOSIZE)
#define USG_VWIN_MINHEIGHT (3 * USG_VWIN_MARGIN + USG_VWIN_TITLEHEIGHT)
#define USG_VWIN_MINWIDTH (2 * (USG_VWIN_MARGIN + USG_VWIN_LOGOSIZE + USG_VWIN_LOGO_MARGIN))

struct _USG_VirtualWindow_STRUCT {
    USG_GameObject frame;

    USG_GameObject title;
    USG_GameObject titleBar;
    USG_GameObject logo;
    USG_GameObject close;

    USG_GameObject contents;

    int bCloseable;
    int bIsGrabbed;

    void * childElement;
    void (*child_onClear)(void* element);
    void (*child_onEvent)(void* element, SDL_Event * event);
};

typedef struct _USG_VirtualWindow_STRUCT * USG_VirtualWindow;

USG_VirtualWindow USG_VWIN_createWindow(const char * windowTitle, const char * logoPath, struct USG_Rect dest);

void UG_VWIN_updateTitle(USG_VirtualWindow window, const char * title);
void UG_VWIN_updateLogo(USG_VirtualWindow window, const char * logo);

void USG_VWIN_close(USG_VirtualWindow window);

void USG_VWIN_onUpdate();
void USG_VWIN_onEvent(SDL_Event event);

void USG_VWIN_clear();

#endif /* __VIRTUALWINDOW_H__ */
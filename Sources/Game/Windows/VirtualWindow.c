#include "Game/Windows/VirtualWindow.h"

#include "Engine/Tools/List.h"
#include "Engine/Tools/Allocator.h"
#include "Engine/Fs/FontLoader.h"

#include <stdio.h>
#include <stdlib.h>

USG_List _USG_VWIN_list() {
    static USG_List list = NULL;

    if (list == NULL) {
        list = USG_LIST_create();
    }

    return list;
}

USG_VirtualWindow USG_VWIN_createWindow(const char * windowTitle, const char * logoPath, struct USG_Rect dest) {
    // Create a new window.
    USG_VirtualWindow window = USG_allocate(1, sizeof(struct _USG_VirtualWindow_STRUCT));

    // Ensure a minimum height.
    if (dest.extent.y < USG_VWIN_MINHEIGHT) {
        dest.extent.y = USG_VWIN_MINHEIGHT;
    } if (dest.extent.x < USG_VWIN_MINWIDTH) {
        dest.extent.x = USG_VWIN_MINWIDTH;
    }

    // Get the predicted text size.
    struct USG_Vector textSize = USG_FONT_predictTextSize(windowTitle, USG_VWIN_PATH_TITLETXT, 32);

    // Compute the different rects.
    struct USG_Rect frame, titleBar, title, logo, close, contents;
    frame = dest;
    titleBar = USG_RECT(
        USG_VWIN_MARGIN, USG_VWIN_MARGIN,
        dest.extent.x - (2 * USG_VWIN_MARGIN), USG_VWIN_TITLEHEIGHT
    );
    title    = USG_RECT(
        (2 * USG_VWIN_LOGOSIZE + USG_VWIN_LOGO_MARGIN), USG_VWIN_LOGO_MARGIN, 
        (USG_VWIN_LOGOSIZE * (textSize.x / textSize.y)), USG_VWIN_LOGOSIZE
    );

    logo = USG_RECT(USG_VWIN_LOGO_MARGIN, USG_VWIN_LOGO_MARGIN, USG_VWIN_LOGOSIZE, USG_VWIN_LOGOSIZE);
    close = USG_RECT(titleBar.extent.x - USG_VWIN_LOGOSIZE - USG_VWIN_LOGO_MARGIN, USG_VWIN_LOGO_MARGIN, USG_VWIN_LOGOSIZE, USG_VWIN_LOGOSIZE);
    contents = USG_RECT(
        USG_VWIN_MARGIN, (2 * USG_VWIN_MARGIN) + titleBar.extent.y, 
        dest.extent.x - (2 * USG_VWIN_MARGIN), dest.extent.y - (3 * USG_VWIN_MARGIN) - titleBar.extent.y
    );

    int zOrder = USG_LIST_size(_USG_VWIN_list());

    // Fill the window.
    window->frame    = USG_createSquare(USG_VWIN_COLOR_WINDOW_BG      , frame, "Desktop-Front" , zOrder);
    window->titleBar = USG_createSquare(USG_VWIN_COLOR_WINDOW_TITLEBAR, titleBar, "Desktop-Front", zOrder);
    window->title    = USG_createText(windowTitle, USG_VWIN_PATH_TITLETXT, 32, USG_VWIN_COLOR_WINDOW_TITLETXT, title, "Desktop-Front", zOrder);
    window->logo     = USG_createSprite(logoPath, USG_RECT_UNIT, logo , "Desktop-Front", zOrder);
    window->close    = USG_createSprite(USG_VWIN_PATH_CROSS, USG_RECT_UNIT, close, "Desktop-Front", zOrder);
    window->contents = USG_createSquare(USG_VWIN_COLOR_WINDOW_CONTENTS, contents, "Desktop-Front", zOrder);

    // Set the parent links.
    window->titleBar->parent = window->frame;
    window->title->parent = window->titleBar;
    window->logo->parent = window->titleBar;
    window->close->parent = window->titleBar;
    window->contents->parent = window->frame;

    window->childElement = NULL;
    window->child_onClear = NULL;
    window->child_onEvent = NULL;

    window->bIsGrabbed = 0;

    // Add the window to the list.
    USG_LIST_append(_USG_VWIN_list(), window);

    // Return the object.
    return window;
}

void UG_VWIN_updateTitle(USG_VirtualWindow window, const char * title) {}
void UG_VWIN_updateLogo(USG_VirtualWindow window, const char * logo) {}

SDL_Event * _USG_VWIN_window_eventStore(SDL_Event * ev) {
    static SDL_Event * store;

    if (ev) store = ev;

    return store;
}

void _USG_VWIN_window_onUpdate(void* element) {}

void _USG_VWIN_window_onEvent(void* element) {
    USG_VirtualWindow window = element;
    SDL_Event * event = _USG_VWIN_window_eventStore(NULL);

    // Check for grab.
    if (event->type == SDL_MOUSEBUTTONDOWN) {
        // Check if the click is left.
        if (event->button.button == SDL_BUTTON_LEFT) {
            // If the mouse is on the title bar.
            struct USG_Rect worldTitleBar = USG_RECT_V(
                USG_GO_getWorldPosition(window->titleBar),
                window->titleBar->dest.extent
            );

            if (USG_R_containsPoint(worldTitleBar, USG_VECTOR(event->button.x, event->button.y))) {
                window->bIsGrabbed = 1;
            }
        }
    // Check for release.
    } else if (event->type == SDL_MOUSEBUTTONUP) {
        // Check if the click is left.
        if (event->button.button == SDL_BUTTON_LEFT) { 
            // Release the window.
            window->bIsGrabbed = 0;
        }
    } else if (event->type == SDL_MOUSEMOTION) {
        // If the window is grabbed.
        if (window->bIsGrabbed) {
            // Move the frame.
            USG_GO_move(window->frame, USG_VECTOR(event->motion.xrel, event->motion.yrel));
        }
    }

    if (window->child_onEvent)
        window->child_onEvent(window->childElement, event);
}

void USG_VWIN_onUpdate() {
    
}

void USG_VWIN_onEvent(SDL_Event event) {
    // Store the event.
    _USG_VWIN_window_eventStore(&event);

    // call the event on each window.
    USG_LIST_forEach(_USG_VWIN_list(), _USG_VWIN_window_onEvent);
}

void USG_VWIN_close(USG_VirtualWindow window) {
    if (window) {
        // Call the child clearer.
        if (window->childElement) {
            window->child_onClear(window->childElement);
        }
        // Delete all game objects.
        USG_destroy(&(window->close));
        USG_destroy(&(window->contents));
        USG_destroy(&(window->frame));
        USG_destroy(&(window->logo));
        USG_destroy(&(window->title));
        USG_destroy(&(window->titleBar));

        // Remove the window from the list.
        USG_LIST_remove(_USG_VWIN_list(), USG_LIST_find(_USG_VWIN_list(), window));
        
        // Deallocate the window.
        USG_deallocate(window);
    }
}


void _USG_VWIN_clearWindow(void* element) {
    if (element) {
        USG_VirtualWindow window = (USG_VirtualWindow)element;

        USG_VWIN_close(window);
    }    
}

void USG_VWIN_clear() {
    USG_LIST_forEach(_USG_VWIN_list(), _USG_VWIN_clearWindow);

    USG_LIST_clear(_USG_VWIN_list());
}
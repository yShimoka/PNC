#include "Game/Windows/Console.h"

#include "Engine/Tools/Allocator.h"
#include "Engine/Fs/FontLoader.h"

#include <string.h>
#include <stdio.h>

/**
 * Clears the contents of the console.
 * Deallocates the lines buffer and the text GameObjects.
 */
void _USG_CON_onClear(void * element) {
    USG_Console console = element;

    // Deallocate the line buffer.
    USG_deallocate(console->text.lines);
    
    // Deallocate the text GameObjects.
    for (int i = 0; i < LINE_COUNT; i++) {
        if(console->text.text[i])  {
            USG_destroy(&(console->text.text[i]));
        }
    }

    // Deallocate the struct.
    USG_deallocate(console);
}

void _USG_CON_onEvent(void* element, SDL_Event event) {
    
}

USG_Console USG_CON_createConsole(const char * title) {
    // Create a new console object.
    USG_Console console = USG_allocate(1, sizeof(struct _USG_Console_STRUCT));

    // Create the window object.
    console->window = USG_VWIN_createWindow(title, USG_TEXTURE_PATH("Console"), USG_RECT(0, 0, (LINE_LENGTH + 1) * CHAR_WIDTH, USG_VWIN_TITLEHEIGHT + (LINE_COUNT + 1) * CHAR_HEIGHT));

    // Set the contents color.
    console->window->contents->renderable->color = USG_COLOR(0, 0, 0, 255);

    // Create the data struct.
    struct ConsoleText text = {};
    // Clear the GameObject list.
    for(int i = 0; i < LINE_COUNT; i++) text.text[i] = NULL;
    // Create the lines buffer.
    text.lines = USG_allocate(LINE_COUNT, sizeof(char *));
    // Initialize the line counter.
    text.currLine = 0;

    console->text = text;

    // Set the child element object.
    console->window->childElement = console;
    console->window->child_onClear = _USG_CON_onClear;
    // Set the update method.
    console->window->child_onEvent = _USG_CON_onEvent;
    
    // Return the console object.
    return console;
}

void USG_CON_print(USG_Console console, const char * line) {
    // Ensure the size of the line.
    if (strlen(line) > LINE_LENGTH) {
        // Log the error.
        fprintf(stderr, "Your line is too long !!!");
        return;
    }
    
    // Get the ConsoleText structure.
    struct ConsoleText * consoleText = &(console->text);

    // Append the text into the lines buffer.
    consoleText->currLine = (consoleText->currLine + 1) % LINE_COUNT;
    consoleText->lines[consoleText->currLine] = line;

    // Update the lines rendering.
    int lineCounter = consoleText->currLine;
    // Loop backwards through the lines.
    for (int i = LINE_COUNT - 1; i >= 0; i--) {

        // If a text GameObject exists, destroy it.
        if (consoleText->text[lineCounter]) USG_destroy(&(consoleText->text[lineCounter]));

        // Compute the position of the text.
        struct USG_Rect rect = USG_RECT(
            2, (i * CHAR_HEIGHT) - CHAR_MARGIN,
            strlen(line) * CHAR_WIDTH, CHAR_HEIGHT
        );

        // Create the new text object.
        consoleText->text[lineCounter] = USG_createText(consoleText->lines[lineCounter], USG_VWIN_PATH_TITLETXT, 24, USG_VWIN_COLOR_WINDOW_TITLETXT, rect, "Desktop-Front", console->window->frame->zOrder);
        consoleText->text[lineCounter]->parent = console->window->contents;

        // Get the previous line in the buffer.
        lineCounter--;
        // Ensure that we are still in the buffer.
        if (lineCounter < 0) lineCounter = LINE_COUNT - 1; 
    }
}
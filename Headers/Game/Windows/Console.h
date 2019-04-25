#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include "Game/Windows/VirtualWindow.h"


#define CHAR_WIDTH 14
#define CHAR_HEIGHT 22

#define CHAR_MARGIN 2

#define LINE_LENGTH 30
#define LINE_COUNT 15

/**
 * Holds the data for the contents of the console.
 */
struct ConsoleText {
    USG_GameObject text[LINE_COUNT];

    const char ** lines;

    int currLine;
};

struct _USG_Console_STRUCT {
    USG_VirtualWindow window;

    struct ConsoleText text;
};

typedef struct _USG_Console_STRUCT * USG_Console;

USG_Console USG_CON_createConsole(const char * title);

void USG_CON_print(USG_Console console, const char * text);

#endif /* __CONSOLE_H__ */
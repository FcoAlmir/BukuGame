#include <stdio.h>
#include <windows.h>

int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Save current attributes to restore later
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    WORD saved_attributes = consoleInfo.wAttributes;

    // Set text color to blue (FOREGROUND_BLUE)
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
    printf("This text is blue in the console.\\n");

    // Combine attributes for different effects (e.g., yellow text on red background)
    // Colors are defined as a combination of foreground and background bits
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | BACKGROUND_RED);
    printf("Yellow text on a red background.\\n");

    // Restore original attributes
    SetConsoleTextAttribute(hConsole, saved_attributes);
    printf("Back to normal text.\\n");

    return 0;
}
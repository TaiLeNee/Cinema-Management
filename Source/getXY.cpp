#include "../Header/getXY.h"

Position getXY() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    Position pos;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        pos.X = csbi.dwCursorPosition.X;
        pos.Y = csbi.dwCursorPosition.Y;
    } else {
        pos.X = pos.Y = -1;
    }
    return pos;
}
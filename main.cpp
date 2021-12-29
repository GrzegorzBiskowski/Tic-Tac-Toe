#include <iostream>
#include <conio.h>
#include "game.h"

int main()
{
    GameStart();
    for (;;)
    {
        PrintBoard();
        if (g_GameState == GS_MOVE)
        {
            unsigned uFieldNumber;
            std::cin >> uFieldNumber;
            Move(uFieldNumber);
        }
        else if (g_GameState == GS_WON || g_GameState == GS_DRAW)
            break;
    }
    getch();
    return 0;
}

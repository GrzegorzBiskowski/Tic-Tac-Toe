#include <iostream>
#include <ctime>
#include <conio.h>
#include "game.h"

FIELD g_aBoard[3][3] = {{FLD_EMPTY, FLD_EMPTY, FLD_EMPTY},
                           {FLD_EMPTY, FLD_EMPTY, FLD_EMPTY},
                           {FLD_EMPTY, FLD_EMPTY, FLD_EMPTY} };
GAMESTATE g_GameState = GS_NOTSTARTED;
SIGN g_CurrentPlayer;

bool GameStart()
{
    if (g_GameState != GS_NOTSTARTED) return false;

    srand (static_cast<unsigned>(time(NULL)));
    g_CurrentPlayer = (rand() % 2 == 0 ? SGN_CIRCLE : SGN_CROSS);
    g_GameState = GS_MOVE;
    return true;
}

bool Move(unsigned uFieldNumber)
{
    if (g_GameState != GS_MOVE) return false;
    if (!(uFieldNumber >= 1 && uFieldNumber <= 9)) return false;

    unsigned uY = (uFieldNumber - 1) / 3;
    unsigned uX = (uFieldNumber - 1) % 3;

    if (g_aBoard[uY][uX] == FLD_EMPTY)
        g_aBoard[uY][uX] = static_cast<FIELD>(g_CurrentPlayer);
    else return false;

    const int LINES[8][3][2] = {{{0, 0}, {0, 1}, {0,2 }},
                            {{1, 0}, {1, 1}, {1, 2}},
                            {{2, 0}, {2, 1}, {2, 2}},
                            {{0, 0}, {1, 0}, {2, 0}},
                            {{0, 1}, {1, 1}, {2, 1}},
                            {{0, 2}, {1, 2}, {2, 2}},
                            {{0, 0}, {1, 1}, {2, 2}},
                            {{2, 0}, {1, 1}, {0, 2}}};
    FIELD Field_, MatchedField;
    unsigned uMatchedFieldsNumber;
    for (int i = 0; i < 8; i++)
    {
        Field_ = MatchedField = FLD_EMPTY;
        uMatchedFieldsNumber = 0;
        for (int j = 0; j < 3; j++)
        {
            Field_ = g_aBoard[LINES[i][j][0]][LINES[i][j][1]];
            if (Field_ != MatchedField)
            {
                MatchedField = Field_;
                uMatchedFieldsNumber = 1;
            } else uMatchedFieldsNumber++;
        }
        if (uMatchedFieldsNumber == 3 && MatchedField != FLD_EMPTY)
        {
            g_GameState = GS_WON;
            return true;
        }
    }
    unsigned uFilledFieldsNumber = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (g_aBoard[i][j] != FLD_EMPTY)
            {
                uFilledFieldsNumber++;
            }
        }
    }
    if (uFilledFieldsNumber == 3*3)
    {
        g_GameState = GS_DRAW;
        return true;
    }
    g_CurrentPlayer = (g_CurrentPlayer == SGN_CIRCLE ? SGN_CROSS : SGN_CIRCLE);
    return true;
}
bool PrintBoard()
{
    if (g_GameState == GS_NOTSTARTED)
    {
        return false;
    }
    system("cls");

    std::cout << "    TIC-TAC-TOE     " << std::endl;
    std::cout << "--------------------" << std::endl;
    std::cout << std::endl;

    std::cout << "        =====" << std::endl;
    for (int i = 0; i < 3; i++)
    {
        std::cout << "        |";
        for (int j = 0; j < 3; j++)
        {
            if (g_aBoard[i][j] == FLD_EMPTY)
                std::cout << i * 3 + j + 1;
            else
                std::cout << static_cast<char>(g_aBoard[i][j]);
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "        =====" << std::endl;
    std::cout << std::endl;

    switch(g_GameState)
    {
    case GS_MOVE:
        std::cout << "Write the field number where" << std::endl;
        std::cout << "you want to place a ";
        std::cout << (g_CurrentPlayer == SGN_CIRCLE ? "circle" : "cross") << ": "; break;
    case GS_WON:
        std::cout << "Player placing ";
        std::cout << (g_CurrentPlayer == SGN_CIRCLE ? "circles" : "crosses") << " wins!" << std::endl;
        std::cout << "Press any key to exit..."; break;
    case GS_DRAW:
        std::cout << "Draw!" << std::endl;
        std::cout << "Press any key to exit..."; break;
    }
    return true;
}

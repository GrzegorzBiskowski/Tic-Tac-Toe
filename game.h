#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

enum SIGN {SGN_CIRCLE = 'O', SGN_CROSS = 'X'};
enum FIELD {FLD_EMPTY, FLD_CIRCLE = SGN_CIRCLE, FLD_CROSS = SGN_CROSS};
enum GAMESTATE {GS_NOTSTARTED, GS_MOVE, GS_WON, GS_DRAW};

bool GameStart();
bool Move(unsigned);
bool PrintBoard();

extern GAMESTATE g_GameState;

#endif // GAME_H_INCLUDED

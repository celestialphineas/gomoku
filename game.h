// Game class interface
#ifndef __GAME_H_
#define __GAME_H_

#include "board.h"
#include "player.h"
#include "winning_judge.h"

class Game
{
public:
    Game();
protected:
    Player *black_player;
    Player *white_player;
};

#endif
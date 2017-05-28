// Game class interface
#ifndef __GAME_H_
#define __GAME_H_

#include "board.h"
#include "player.h"
#include "free_style_judge.h"

// Game abstract interface
class Game
{
public:
    Game()
    {board = NULL;   judge = NULL;
        black_player = white_player = NULL;}
    Game(const Game&);
    virtual ~Game();
    void exchange_player();
    void set_board(const Board*);
    void set_judge(const WinningJudge*);
    void set_black(const Player*);
    void set_white(const Player*);
    virtual void request_te() = 0;
protected:
    // A game instance has its own components!
    // The pointers below each point to an unique instance.
    Board *board;
    WinningJudge *judge;
    Player *black_player;
    Player *white_player;
};

#endif
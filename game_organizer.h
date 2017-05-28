// Header file for Game class interface
#ifndef __GAME_ORGANIZER_H_
#define __GAME_ORGANIZER_H_

#include "board.h"
#include "player.h"
#include "free_style_judge.h"

// Game organizer abstract interface
class GameOrganizer
{
public:
    GameOrganizer(const GameOrganizer&);
    GameOrganizer(Board *_board = NULL, WinningJudge *_judge = NULL,
        Player *_black = NULL, Player *_white = NULL);
    virtual ~GameOrganizer() {return;}
    // The exchange_player method exchanges the pointers "black_player" and 
    // "white_player", if no NULL occurs, the method also let the players change
    // the stones that they are playing.
    void exchange_player();
    void set_board(Board *_board) {board = _board;}
    void set_judge(WinningJudge *_judge) {judge = _judge;}
    void set_black(Player*);
    void set_white(Player*);
    virtual bool request_te() = 0;
protected:
    // A game instance has its own components!
    // The pointers below each point to an unique instance.
    Board *board;
    WinningJudge *judge;
    Player *black_player;
    Player *white_player;
};

#endif
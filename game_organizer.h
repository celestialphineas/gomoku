// Header file for Game class interface
#ifndef __GAME_ORGANIZER_H_
#define __GAME_ORGANIZER_H_

#include <cstdlib>
#include "board.h"
#include "player.h"

// Game organizer abstract interface
class GameOrganizer
{
public:
    typedef unsigned CurrentRequest;
    static const CurrentRequest game_ends = 0;
    static const CurrentRequest black_te = 1;
    static const CurrentRequest black_remove = 2;
    static const CurrentRequest black_exchange = 3;
    static const CurrentRequest white_te = 4;
    static const CurrentRequest white_remove = 5;
    static const CurrentRequest white_exchange = 6;
    GameOrganizer(const GameOrganizer&);
    GameOrganizer(Board *_board = NULL, WinningJudge *_judge = NULL,
        Player *_black = NULL, Player *_white = NULL);
    virtual ~GameOrganizer() {return;}
    virtual GameOrganizer* clone() const = 0;
    // The exchange_player method exchanges the pointers "black_player" and 
    // "white_player", if no NULL occurs, the method also let the players change
    // the stones that they are playing.
    void exchange_player();
    void set_board(Board *_board) {board = _board;}
    void set_judge(WinningJudge *_judge) {judge = _judge;}
    void set_black(Player*);
    void set_white(Player*);
    Player *get_black() const {return black_player;}
    Player *get_white() const {return white_player;}
    WinningJudge *get_judge() const {return judge;}
    WinningJudge::CurrentWinLoss game_status() const
        {if(judge) return judge->judge(); else return WinningJudge::ongoing;}
    virtual void next() = 0;
    CurrentRequest current_request() const {return current_request_status;}
protected:
    // A game instance has its own components!
    // The pointers below each point to an unique instance.
    Board *board;
    WinningJudge *judge;
    Player *black_player;
    Player *white_player;
    CurrentRequest current_request_status;
};

#endif
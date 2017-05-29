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
    typedef unsigned CurrentRequest;
    static const CurrentRequest invalid = 0;
    static const CurrentRequest black_te = 1;
    static const CurrentRequest black_remove = 2;
    static const CurrentRequest white_te = 3;
    static const CurrentRequest white_remove = 4;
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
    Player *get_black() const {return black_player;}
    Player *get_white() const {return white_player;}
    WinningJudge *get_judge() const {return judge;}
    WinningJudge::GameStatus game_status()
        {if(judge) return judge->judge(); else return WinningJudge::ongoing;}
    virtual void next() = 0;
    CurrentRequest current_request() {return current_request_status;}
    friend class SingleGameFactory;
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
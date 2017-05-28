// Header file for the player base class
// Celestial Phineas @ ZJU
#ifndef __PLAYER_H
#define __PLAYER_H

#include <vector>
#include "board.h"
#include "winning_judge.h"
#include "te.h"

// The Player class defines an interface for the players. The player have a 
// pointer to the board (a player, either a human or an AI must have an eye on
// the gomoku board), and a stone_color (he must know what stone he is playing).
// To ask the player to make a dicision on a te, the te method should be used.
// And the remove method is used to let the player to remove a stone from the 
// given candidates (type std::vector<Te>).
class Player
{
public:
    static const bool black = false;
    static const bool white = true;
    Player(Board *_board, bool _stone) {board = _board; stone_color = _stone;}
    Player(const Player &src)
        {board = src.board; stone_color = src.stone_color;}
    virtual ~Player() {return;}
    // We need a clone method to request an instance with a base class pointer.
    virtual Player *clone() const = 0;
    bool is_black() const {return !stone_color;}
    bool is_white() const {return stone_color;}
    void set_board(Board *_board) {board = _board;}
    void set_stone(bool _stone) {stone_color = _stone;}
    virtual bool te() = 0;
    virtual bool remove(const std::vector<Te> te_candidates);
protected:
    Board *board;
    bool stone_color;
};

class AIPlayer: public Player
{
public:
    AIPlayer(Board *_board, bool _stone, WinningJudge *_judge)
        : Player(_board, _stone) {judge = _judge;}
    AIPlayer(const AIPlayer &src): Player(src) {judge = src.judge;}
    ~AIPlayer() {return;}
    // virtual Player *clone() const;
    void set_judge(WinningJudge *_judge) {judge = _judge;}
protected:
    WinningJudge *judge;
};

#endif
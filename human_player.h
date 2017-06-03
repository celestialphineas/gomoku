#ifndef __HUMAN_PLAYER_H_
#define __HUMAN_PLAYER_H_

#include "player.h"

class HumanPlayer: public Player
{
public:
    HumanPlayer(Board *_board, bool _stone, WinningJudge *_judge)
        : Player(_board, _stone)
            {there_is_something_in = false;}
    HumanPlayer(const HumanPlayer &src): Player(src)
        {there_is_something_in = src.there_is_something_in;}
    PlayerType player_type() const {return human_player;}
    Player *clone() const {return new HumanPlayer(*this);}
    // Return false if the input is rejected.
    bool input(unsigned x, unsigned y);
    bool got_input() const {return there_is_something_in;}
    bool te();
    bool remove(const std::vector<Te> te_candidates);
private:
    bool there_is_something_in;
    unsigned x_buf; unsigned y_buf;
};

#endif
#ifndef __HUMAN_PLAYER_H_
#define __HUMAN_PLAYER_H_

#include "../player.h"

class HumanPlayer: public Player
{
public:
    HumanPlayer(Board *_board, bool _stone)
        : Player(_board, _stone)
    {
        there_is_something_in = false;
        exchange_choice_buf = false;
    }
    HumanPlayer(const HumanPlayer &src): Player(src)
        {there_is_something_in = src.there_is_something_in;}
    PlayerType player_type() const {return human_player;}
    Player *clone() const {return new HumanPlayer(*this);}
    HumanPlayer &operator=(const HumanPlayer &src)
        {return *(new HumanPlayer(src));}
    // Return false if the input is rejected.
    bool input(unsigned x, unsigned y);
    bool input(bool _exchange_choice);
    bool got_input() const {return there_is_something_in;}
    bool te();
    bool remove();
    bool exchange_choice() {return exchange_choice_buf;};
private:
    bool there_is_something_in;
    unsigned x_buf; unsigned y_buf;
    bool exchange_choice_buf;
};

#endif
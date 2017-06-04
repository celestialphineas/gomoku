#include "human_player.h"

bool HumanPlayer::input(unsigned x, unsigned y)
{
    if(remove_candidates.empty())
    {
        if(board->get_status(x, y) == Board::accessible)
        {
            x_buf = x; y_buf = y;
            there_is_something_in = true;
            return true;
        }
    }
    else
    {
        bool found = false;
        for(std::vector<Te>::const_iterator i = remove_candidates.begin();
            i != remove_candidates.end(); i++)
        {
            if(i->x() == x && i->y() == y) {found = true; break;}
        }
        if(found)
        {
            x_buf = x; y_buf = y;
            there_is_something_in = true;
            return true;
        }
    }
    return false;
}

bool HumanPlayer::input(bool _exchange_choice)
{
    exchange_choice_buf = _exchange_choice;
    return true;
}

bool HumanPlayer::te()
{
    if(!there_is_something_in) return false;
    if(stone_color == black)
    {
        bool result = board->black_te(x_buf, y_buf);
        there_is_something_in = false;
        return result;
    }
    else
    {
        bool result = board->white_te(x_buf, y_buf);
        there_is_something_in = false;
        return result;
    }
    return false;
}

bool HumanPlayer::remove()
{
    if(!there_is_something_in) return false;
    if(stone_color == black)
    {
        bool result = board->black_remove(x_buf, y_buf);
        there_is_something_in = false;
        return result;
    }
    else
    {
        bool result = board->white_remove(x_buf, y_buf);
        there_is_something_in = false;
        return result;
    }
    return false;
}
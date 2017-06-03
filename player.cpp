#include "player.h"

bool Player::remove()
{
    if(remove_candidates.empty()) return false;
    if(this->is_black())
        return board->black_remove(remove_candidates[0].x(), remove_candidates[0].y());
    else
        return board->white_remove(remove_candidates[0].x(), remove_candidates[0].y());
}
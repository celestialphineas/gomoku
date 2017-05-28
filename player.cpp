#include "player.h"

bool Player::remove(const std::vector<Te> te_candidates)
{
    if(te_candidates.empty()) return false;
    if(this->is_black())
        return board->black_remove(te_candidates[0].x(), te_candidates[0].y());
    else
        return board->white_remove(te_candidates[0].x(), te_candidates[0].y());
}
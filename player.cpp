#include "player.h"

void Player::remove(const std::vector<Te> te_candidates)
{
    if(te_candidates.empty()) return;
    if(this->is_black())
        board->black_remove(te_candidates[0].x(), te_candidates[0].y());
    else
        board->white_remove(te_candidates[0].x(), te_candidates[0].y());
    return;
}
#include "std_organizer.h"

void StdOrganizer::next()
{
    if(game_status() != WinningJudge::ongoing
        || board->full())
        current_request_status = game_ends;
    if(current_request_status == black_te)
        current_request_status = white_te;
    else
        current_request_status = black_te;
    return;
}

#include "std_organizer.h"

bool StdOrganizer::request_te()
{
    if(request_black)
    {
        request_black = false;
        if(!black_player) return false;
        return black_player->te();
    }
    else
    {
        request_black = true;
        if(!white_player) return false;
        return white_player->te();
    }
}
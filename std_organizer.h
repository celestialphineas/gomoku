// Header file for standard game organizer
// i.e. black first, then white, then black...
// without Yamaguchi or something like that.
#ifndef __STD_ORGANIZER_H_
#define __STD_ORGANIZER_H_

#include "game_organizer.h"

class StdOrganizer: public GameOrganizer
{
public:
    StdOrganizer(Board *_board = NULL, WinningJudge *_judge = NULL,
        Player *_black = NULL, Player *_white = NULL):
            GameOrganizer(_board, _judge, _black, _white)
                {request_black = true;}
    // Copy constructors
    StdOrganizer(const StdOrganizer &src): GameOrganizer(src)
        {request_black = src.request_black;}
    StdOrganizer(const GameOrganizer &src): GameOrganizer(src)
        {request_black = true;}
    // Destructor
    ~StdOrganizer() {return;}
    bool request_te();
private:
    // This is to mark the one to te.
    bool request_black;
};

#endif
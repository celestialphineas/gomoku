// Header file for standard game organizer
// i.e. black first, then white, then black...
// without Yamaguchi or something like that.
#ifndef __STD_ORGANIZER_H_
#define __STD_ORGANIZER_H_

#include "../game_organizer.h"

class StdOrganizer: public GameOrganizer
{
public:
    StdOrganizer(Board *_board = NULL, WinningJudge *_judge = NULL,
        Player *_black = NULL, Player *_white = NULL):
            GameOrganizer(_board, _judge, _black, _white) {}
    // Copy constructors
    StdOrganizer(const StdOrganizer &src): GameOrganizer(src) {}
    StdOrganizer(const GameOrganizer &src): GameOrganizer(src) {}
    StdOrganizer &operator=(const StdOrganizer &src)
        {return *(new StdOrganizer(src));}
    // Destructor
    ~StdOrganizer() {return;}
    GameOrganizer *clone() const {return new StdOrganizer(*this);}
    void next();
};

#endif
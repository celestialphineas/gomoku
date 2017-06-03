#ifndef __PRIMARY_AI_H_
#define __PRIMARY_AI_H_

#include <ctime>
#include <cstdlib>
#include "player.h"
#include "threat_finder.h"
#include "winning_judge.h"

class PrimaryAI: public AIPlayer
{
public:
    PrimaryAI(Board *_board, bool _stone, WinningJudge *_judge)
        : AIPlayer(_board, _stone, _judge) {}
    PrimaryAI(const AIPlayer &src): AIPlayer(src) {}
    Player *clone() const {return new PrimaryAI(*this);}
    bool te();
    bool remove();
    bool exchange_choice();
};

#endif
#ifndef __STD_GOMOKU_JUDGE_
#define __STD_GOMOKU_JUDGE_

#include "../winning_judge.h"

class StandardGomokuJudge: public WinningJudge
{
public:
    StandardGomokuJudge(Board *_board): WinningJudge(_board) {};
    StandardGomokuJudge(const WinningJudge &src): WinningJudge(src) {};
    ~StandardGomokuJudge() {};
    StandardGomokuJudge &operator=(const StandardGomokuJudge &src)
        {return *(new StandardGomokuJudge(src));}
    CurrentWinLoss judge();
    WinningJudge *clone() const {return new StandardGomokuJudge(*this);}
};

#endif
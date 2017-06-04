#ifndef __FREE_STYLE_JUDGE_
#define __FREE_STYLE_JUDGE_

#include "../winning_judge.h"

// Free style gomoku is an easy form of gomoku requires no exact-five rule
class FreeStyleJudge: public WinningJudge
{
public:
    FreeStyleJudge(Board *_board): WinningJudge(_board) {};
    FreeStyleJudge(const WinningJudge &src): WinningJudge(src) {};
    ~FreeStyleJudge() {};
    CurrentWinLoss judge();
    WinningJudge *clone() const {return new FreeStyleJudge(*this);}
};

#endif
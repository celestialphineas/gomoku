//
//  forbidden_judge.h
//  forbidden_judge
//
//  Created by 邓婕 on 2017/6/1.
//  Copyright © 2017年 邓婕. All rights reserved.
//

#ifndef forbidden_judge_h
#define forbidden_judge_h

#include "../winning_judge.h"

//The class ForbiddenJudge inherits from the class WinningJudge.
class ForbiddenJudge: public WinningJudge
{
public:
    ForbiddenJudge(Board *_board): WinningJudge(_board) {};
    ForbiddenJudge(const WinningJudge &src): WinningJudge(src) {};
    ~ForbiddenJudge() {};
    CurrentWinLoss judge();
    WinningJudge *clone() const {return new ForbiddenJudge(*this);}
    
private:
    //Define a vector "forbidden_points" to store the forbidden points, which are from the previous chessboard
    //and can help to check whether the recent moved black stone is put at the forbidden point.
    std::vector<std::vector<unsigned> > forbidden_points;
};

#endif /* forbidden_judge_h */

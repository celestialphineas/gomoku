#ifndef __WINNING_JUDGE_
#define __WINNING_JUDGE_

#include "board.h"

// Judge base class
class WinningJudge
{
protected:
    Board *board;
    // Below are coordinates of the markers (we need markers to indicate the
    // in-row stones on GUI)
    unsigned marker1_x;
    unsigned marker1_y;
    unsigned marker2_x;
    unsigned marker2_y;
    // Just consider the generalized condition...
    // It can be useful to let it independent from the judge algorithm.
    unsigned n_in_row;
public:
    static const unsigned undef = 0xffffffff;
    typedef unsigned GameStatus;
    static const GameStatus ongoing = 0;
    static const GameStatus black_wins = 1;
    static const GameStatus white_wins = 2;
    WinningJudge(Board *_board)
    {
        board = _board;
        marker1_x = undef; marker1_y = undef;
        marker2_x = undef; marker2_y = undef;
        n_in_row = 5;
        return;
    }
    WinningJudge(const WinningJudge &src) {this->board = src.board;}
    virtual ~WinningJudge() {return;}
    // Get the marker coodinates (see private scope below)
    unsigned get_marker1_x() const {return marker1_x;}
    unsigned get_marker1_y() const {return marker1_y;}
    unsigned get_marker2_x() const {return marker2_x;}
    unsigned get_marker2_y() const {return marker2_y;}
    virtual GameStatus judge() = 0;
};

#endif
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
    typedef unsigned CurrentWinLoss;
    static const CurrentWinLoss ongoing = 0;
    static const CurrentWinLoss black_wins = 1;
    static const CurrentWinLoss white_wins = 2;
    WinningJudge(Board *_board)
    {
        board = _board;
        marker1_x = undef; marker1_y = undef;
        marker2_x = undef; marker2_y = undef;
        n_in_row = 5;
        return;
    }
    WinningJudge(const WinningJudge &src)
    {
        this->board = src.board;
        marker1_x = src.marker1_x; marker1_y = src.marker1_y;
        marker2_x = src.marker2_x; marker2_y = src.marker2_y;
        n_in_row = src.n_in_row;
        return;
    }
    virtual ~WinningJudge() {return;}
    WinningJudge &operator=(const WinningJudge &src)
        {return *(new WinningJudge(src));}
    void set_board(Board *_board) {board = _board;}
    // We need a clone method to request an instance with a base class pointer.
    virtual WinningJudge *clone() const = 0;
    // Get the marker coodinates (see private scope below)
    unsigned get_marker1_x() const {return marker1_x;}
    unsigned get_marker1_y() const {return marker1_y;}
    unsigned get_marker2_x() const {return marker2_x;}
    unsigned get_marker2_y() const {return marker2_y;}
    virtual CurrentWinLoss judge() = 0;
};

#endif
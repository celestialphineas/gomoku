//
//  main.cpp
//  forbidden_judge
//
//  Created by 邓婕 on 2017/6/1.
//  Copyright © 2017年 邓婕. All rights reserved.
//

#include "forbidden_judge.h"
#include "std_gomoku_judge.h"

static const unsigned NO_FORBIDDEN          = 0;
static const unsigned THREE_THREE_FORBIDDEN = 1;
static const unsigned FOUR_FOUR_FORBIDDEN   = 2;
static const unsigned LONG_FORBIDDEN        = 3;

static int KeyPointForbiddenCheck(Board *board, unsigned x, unsigned y, int point_b, int direction);

static int ForbiddenCheck(Board *board, unsigned x, unsigned y)
{
    int point_b[8];
    int point_ba[8];
    int point_bab[8];
    int point_baba[8];
    int point_babab[8];
    
    //Set all of the counters as 0
    for(unsigned i=0; i<8; i++)
    {
        point_b[i] = point_ba[i] = point_bab[i] = 0;
        point_baba[i] = point_babab[i] = 0;
    }
    
    unsigned int _x, _y;
    
    //Check the top
    for(_y = y-1; _y >= 1 && board->get_status(x, _y) == Board::black_stone; _y--, point_b[0]++);
    for(; _y >= 1 && board->get_status(x, _y) == Board::accessible; _y--, point_ba[0]++);
    for(; _y >= 1 && board->get_status(x, _y) == Board::black_stone; _y--, point_bab[0]++);
    for(; _y >= 1 && board->get_status(x, _y) == Board::accessible; _y--, point_baba[0]++);
    for(; _y >= 1 && board->get_status(x, _y) == Board::black_stone; _y--, point_babab[0]++);
    
    //Check the top-right
    for(_x = x+1, _y = y-1; _x <= board->n_col() && _y >= 1 && board->get_status(_x, _y) == Board::black_stone; _x++, _y--, point_b[1]++);
    for(; _x <= board->n_col() && _y >= 1 && board->get_status(_x, _y) == Board::accessible; _x++, _y--, point_ba[1]++);
    for(; _x <= board->n_col() && _y >= 1 && board->get_status(_x, _y) == Board::black_stone; _x++, _y--, point_bab[1]++);
    for(; _x <= board->n_col() && _y >= 1 && board->get_status(_x, _y) == Board::accessible; _x++, _y--, point_baba[1]++);
    for(; _x <= board->n_col() && _y >= 1 && board->get_status(_x, _y) == Board::black_stone; _x++, _y--, point_babab[1]++);
    
    //Check the right
    for(_x = x+1; _x <= board->n_col() && board->get_status(_x, y) == Board::black_stone; _x++, point_b[2]++);
    for(; _x <= board->n_col() && board->get_status(_x, y) == Board::accessible; _x++, point_ba[2]++);
    for(; _x <= board->n_col() && board->get_status(_x, y) == Board::black_stone; _x++, point_bab[2]++);
    for(; _x <= board->n_col() && board->get_status(_x, y) == Board::accessible; _x++, point_baba[2]++);
    for(; _x <= board->n_col() && board->get_status(_x, y) == Board::black_stone; _x++, point_babab[2]++);
    
    //Check the bottom_right
    for(_x = x+1, _y = y+1; _x <= board->n_col() && _y <= board->n_row() && board->get_status(_x, _y) == Board::black_stone; _x++, _y++, point_b[3]++);
    for(; _x <= board->n_col() && _y <= board->n_row() && board->get_status(_x, _y) == Board::accessible; _x++, _y++, point_ba[3]++);
    for(; _x <= board->n_col() && _y <= board->n_row() && board->get_status(_x, _y) == Board::black_stone; _x++, _y++, point_bab[3]++);
    for(; _x <= board->n_col() && _y <= board->n_row() && board->get_status(_x, _y) == Board::accessible; _x++, _y++, point_baba[3]++);
    for(; _x <= board->n_col() && _y <= board->n_row() && board->get_status(_x, _y) == Board::black_stone; _x++, _y++, point_babab[3]++);
    
    //Check the bottom
    for(_y = y+1; _y <= board->n_row() && board->get_status(x, _y) == Board::black_stone; _y++, point_b[4]++);
    for(; _y <= board->n_row() && board->get_status(x, _y) == Board::accessible; _y++, point_ba[4]++);
    for(; _y <= board->n_row() && board->get_status(x, _y) == Board::black_stone; _y++, point_bab[4]++);
    for(; _y <= board->n_row() && board->get_status(x, _y) == Board::accessible; _y++, point_baba[4]++);
    for(; _y <= board->n_row() && board->get_status(x, _y) == Board::black_stone; _y++, point_babab[4]++);
    
    //Check the bottom-left
    for(_x = x-1, _y = y+1; _x >=1 && _y <= board->n_row() && board->get_status(_x, _y) == Board::black_stone; _x--, _y++, point_b[5]++);
    for(; _x >=1 && _y <= board->n_row() && board->get_status(_x, _y) == Board::accessible; _x--, _y++, point_ba[5]++);
    for(; _x >=1 && _y <= board->n_row() && board->get_status(_x, _y) == Board::black_stone; _x--, _y++, point_bab[5]++);
    for(; _x >=1 && _y <= board->n_row() && board->get_status(_x, _y) == Board::accessible; _x--, _y++, point_baba[5]++);
    for(; _x >=1 && _y <= board->n_row() && board->get_status(_x, _y) == Board::black_stone; _x--, _y++, point_babab[5]++);
    
    //Check the left
    for(_x = x-1; _x >=1 && board->get_status(_x, y) == Board::black_stone; _x++, point_b[6]++);
    for(; _x >=1 && board->get_status(_x, y) == Board::accessible; _x++, point_ba[6]++);
    for(; _x >=1 && board->get_status(_x, y) == Board::black_stone; _x++, point_bab[6]++);
    for(; _x >=1 && board->get_status(_x, y) == Board::accessible; _x++, point_baba[6]++);
    for(; _x >=1 && board->get_status(_x, y) == Board::black_stone; _x++, point_babab[6]++);
    
    //Check the top-left
    for(_x = x-1, _y = y-1; _x >= 1 && _y >=1 && board->get_status(_x, _y) == Board::black_stone; _x--, _y--, point_b[7]++);
    for(; _x >= 1 && _y >=1 && board->get_status(_x, _y) == Board::accessible; _x--, _y--, point_ba[7]++);
    for(; _x >= 1 && _y >=1 && board->get_status(_x, _y) == Board::black_stone; _x--, _y--, point_bab[7]++);
    for(; _x >= 1 && _y >=1 && board->get_status(_x, _y) == Board::accessible; _x--, _y--, point_baba[7]++);
    for(; _x >= 1 && _y >=1 && board->get_status(_x, _y) == Board::black_stone; _x--, _y--, point_babab[7]++);
    
    for(unsigned i = 0; i < 4; i++)
    {
        if(point_b[i] + point_b[i+4] == 4)
            return NO_FORBIDDEN;
    }
    
    int threecount = 0, fourcount = 0;
    
    for(unsigned i = 0; i < 4; i++)
    {
        if(point_b[i] + point_b[i+4] >= 5)
            return LONG_FORBIDDEN;
        
        else if(point_b[i] + point_b[i+4] == 3)
        {
            bool isFour = false;
            if(point_ba[i] > 0)
            {
                if(KeyPointForbiddenCheck(board, x, y, point_b[i], i) == NO_FORBIDDEN)
                    isFour = true;
            }
            
            if(point_ba[i+4] > 0)
            {
                if(KeyPointForbiddenCheck(board, x, y, point_b[i+4], i+4) == NO_FORBIDDEN)
                    isFour = true;
            }
            if(isFour)
                fourcount++;
        }
        else if(point_b[i] + point_b[i+4] == 2)
        {
            if(point_ba[i] == 1 && point_bab[i] == 1)
            {
                if(KeyPointForbiddenCheck(board, x, y, point_b[i], i) == NO_FORBIDDEN)
                    fourcount++;
            }
            if(point_ba[i+4] == 1 && point_bab[i+4] == 1)
            {
                if(KeyPointForbiddenCheck(board, x, y, point_b[i+4], i+4) == NO_FORBIDDEN)
                    fourcount++;
            }
            
            bool isThree = false;
            if((point_ba[i] > 2 || (point_ba[i] == 2 && point_bab[i] == 0)) && (point_ba[i+4] > 1 || (point_ba[i+4] == 1 && point_bab[i+4] == 0)))
            {
                if(KeyPointForbiddenCheck(board, x, y, point_b[i], i) == NO_FORBIDDEN)
                    isThree = true;
            }
            if((point_ba[i+4] > 2 || (point_ba[i+4] == 2 && point_bab[i+4] == 0)) && (point_ba[i] > 1 || (point_ba[i] == 1 && point_bab[i] == 0)))
            {
                if(KeyPointForbiddenCheck(board, x, y, point_b[i+4], i+4) == NO_FORBIDDEN)
                    isThree = true;
            }
            if(isThree)
                threecount++;
        }
        else if(point_b[i] + point_b[i+4] == 1)
        {
            if(point_ba[i] == 1 && point_bab[i] ==2)
            {
                if(KeyPointForbiddenCheck(board, x, y, point_b[i], i) == NO_FORBIDDEN)
                    fourcount++;
            }
            if(point_ba[i+4] == 1 && point_bab[i+4] ==2)
            {
                if(KeyPointForbiddenCheck(board, x, y, point_b[i+4], i+4) == NO_FORBIDDEN)
                    fourcount++;
            }
            if((point_ba[i] == 1 && point_bab[i] == 1 && point_baba[i] > 1) || (point_baba[i] == 1 && point_babab[i] == 0 && point_ba[i+4] > 1) || (point_ba[i+4] == 1 && point_bab[i+4] == 0))
            {
                if(KeyPointForbiddenCheck(board, x, y, point_b[i], i) == NO_FORBIDDEN)
                    threecount++;
            }
            if((point_ba[i+4] == 1 && point_bab[i+4] == 1 && point_baba[i+4] > 1) || (point_baba[i+4] == 1 && point_babab[i+4] == 0 && point_ba[i] > 1) || (point_ba[i] == 1 && point_bab[i] == 0))
            {
                if(KeyPointForbiddenCheck(board, x, y, point_b[i+4], i+4) == NO_FORBIDDEN)
                    threecount++;
            }
        }
        else if(point_b[i] + point_b[i+4] == 0)
        {
            if(point_ba[i] == 1 && point_bab[i] == 3)
            {
                if(KeyPointForbiddenCheck(board, x, y, point_b[i], i) == NO_FORBIDDEN)
                    fourcount++;
            }
            if(point_ba[i+4] == 1 && point_bab[i+4] == 3)
            {
                if(KeyPointForbiddenCheck(board, x, y, point_b[i+4], i+4) == NO_FORBIDDEN)
                    fourcount++;
            }
            if(point_ba[i] == 1 && point_bab[i] == 2 && (point_baba[i] > 1 || (point_baba[i] == 1 && point_babab[i] == 0)) && (point_ba[i+4] > 1 || (point_ba[i+4] == 1 && point_bab[i+4] == 0)))
            {
                if(KeyPointForbiddenCheck(board, x, y, point_b[i], i) == NO_FORBIDDEN)
                    threecount++;
            }
            if(point_ba[i+4] == 1 && point_bab[i+4] == 2 && (point_baba[i+4] > 1 || (point_baba[i+4] == 1 && point_babab[i+4] == 0)) && (point_ba[i] > 1 || (point_ba[i] == 1 && point_bab[i] == 0)))
            {
                if(KeyPointForbiddenCheck(board, x, y, point_b[i+4], i+4) == NO_FORBIDDEN)
                    threecount++;
            }
        }
    }
    
    if(fourcount > 1)
        return FOUR_FOUR_FORBIDDEN;
    if(threecount > 1)
        return THREE_THREE_FORBIDDEN;
    return NO_FORBIDDEN;
}

static int KeyPointForbiddenCheck(Board *board, unsigned x, unsigned y, int point_b, int direction)
{
    unsigned i, j;
    point_b++;
    if(direction >= 4)
        point_b = -point_b;
    
    switch (direction % 4) {
        case 0:
            i = x;
            j = y - point_b;
            break;
        case 1:
            i = x + point_b;
            j = y - point_b;
            break;
        case 2:
            i = x + point_b;
            j = y;
            break;
        default:
            i = x + point_b;
            j = y + point_b;
            break;
    }
    
    int result = ForbiddenCheck(board, i, j);
    return result;
}

ForbiddenJudge::CurrentWinLoss ForbiddenJudge::judge()
{
    std::vector<unsigned> coord;
    for(unsigned i = 1; i <= board->n_col(); i++)
    {
        for(unsigned j=1; j <= board->n_row(); j++)
        {
            if(board->get_status(coord[0], coord[1]) == Board::black_stone)
                return white_wins;
            if(ForbiddenCheck(board, i, j) == LONG_FORBIDDEN || ForbiddenCheck(board, i, j) == FOUR_FOUR_FORBIDDEN || ForbiddenCheck(board, i, j) == THREE_THREE_FORBIDDEN)
                forbidden_points.push_back(coord);
            else if(ForbiddenCheck(board, i, j) == NO_FORBIDDEN)
                return ongoing;
        }
    }
    StandardGomokuJudge std_judge(board);
    return std_judge.judge();
}

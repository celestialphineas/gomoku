//
//  main.cpp
//  forbidden_judge
//
//  Created by 邓婕 on 2017/6/1.
//  Copyright © 2017年 邓婕. All rights reserved.
//

#include "forbidden_judge.h"
#include "std_gomoku_judge.h"

//According to the international gomoku stadards, it is the player holding the black stones that moves firstly. And the first player can be proved to always win in thoery. Therefore, the forbidden judge only focuses on the black stones. And in general, there are three kinds of forbidden: THREE-THREE FORBIDDEN, FOUR-FOUR FORBIDDEN and LONG FORBIDDEN.
//My algorithm is as follows: Firstly, I check every point of present chessboard to find the possible forbidden points. And then I store these points in a private vector. Next, after each player moving a new stone, check whether the black stone is put at the forbidden points. If yes, the white wins; if not, the game will continue and the private vector that stores forbidden points will be updated. Finally, by repeating the previous step, we can get the game result under forbidden judge.
//The most difficult part of my algorithm is the first step: finding the forbidden points, because there are many conditions in THREE-THREE FORBIDDEN and FOUR-FOUR FORBIDDEN. And I have to take all of the conditions into consideration, which is a logical problem.

static const unsigned NO_FORBIDDEN          = 0;
static const unsigned THREE_THREE_FORBIDDEN = 1;
static const unsigned FOUR_FOUR_FORBIDDEN   = 2;
static const unsigned LONG_FORBIDDEN        = 3;

static int KeyPointForbiddenCheck(Board *board, unsigned x, unsigned y, int point_b, int direction);

//In this function, x is the horizontal coordinate of the point to be checked, and y is the vertical coordinate of the point to be checked. So the point to be checked can be written as (x,y) in coordinates. Board is the present status of the chessboard.
static int ForbiddenCheck(Board *board, unsigned x, unsigned y)
{
    //Define five counters to help searching the chessboard, and every counter has eight elements that represent eight directions, where 0 means the top, 1 means the top-right, 2 means the right, 3 means the bottom-right, 4 means the bottom, 5 means the bottom-left, 6 means the left and 7 means the top-left.
    int point_b[8]; //Count the number of the nearest black stones to (x,y).
    int point_ba[8]; //Count the number of the nearest accessible points to (x,y).
    int point_bab[8]; //Count the number of the second nearest black stones to (x,y).
    int point_baba[8]; //Count the number of the second nearest accessible points to (x,y).
    int point_babab[8]; //Count the number of the third nearest black stones to (x,y).
    
    //Set all of the counters as 0.
    for(unsigned i=0; i<8; i++)
    {
        point_b[i] = point_ba[i] = point_bab[i] = 0;
        point_baba[i] = point_babab[i] = 0;
    }
    
    //Begin searching the chessboard.
    
    unsigned int _x, _y;
    
    //Check the top of (x,y).
    for(_y = y-1; _y >= 1 && board->get_status(x, _y) == Board::black_stone; _y--, point_b[0]++);
    for(; _y >= 1 && board->get_status(x, _y) == Board::accessible; _y--, point_ba[0]++);
    for(; _y >= 1 && board->get_status(x, _y) == Board::black_stone; _y--, point_bab[0]++);
    for(; _y >= 1 && board->get_status(x, _y) == Board::accessible; _y--, point_baba[0]++);
    for(; _y >= 1 && board->get_status(x, _y) == Board::black_stone; _y--, point_babab[0]++);
    
    //Check the top-right of (x,y).
    for(_x = x+1, _y = y-1; _x <= board->n_col() && _y >= 1 && board->get_status(_x, _y) == Board::black_stone; _x++, _y--, point_b[1]++);
    for(; _x <= board->n_col() && _y >= 1 && board->get_status(_x, _y) == Board::accessible; _x++, _y--, point_ba[1]++);
    for(; _x <= board->n_col() && _y >= 1 && board->get_status(_x, _y) == Board::black_stone; _x++, _y--, point_bab[1]++);
    for(; _x <= board->n_col() && _y >= 1 && board->get_status(_x, _y) == Board::accessible; _x++, _y--, point_baba[1]++);
    for(; _x <= board->n_col() && _y >= 1 && board->get_status(_x, _y) == Board::black_stone; _x++, _y--, point_babab[1]++);
    
    //Check the right of (x,y).
    for(_x = x+1; _x <= board->n_col() && board->get_status(_x, y) == Board::black_stone; _x++, point_b[2]++);
    for(; _x <= board->n_col() && board->get_status(_x, y) == Board::accessible; _x++, point_ba[2]++);
    for(; _x <= board->n_col() && board->get_status(_x, y) == Board::black_stone; _x++, point_bab[2]++);
    for(; _x <= board->n_col() && board->get_status(_x, y) == Board::accessible; _x++, point_baba[2]++);
    for(; _x <= board->n_col() && board->get_status(_x, y) == Board::black_stone; _x++, point_babab[2]++);
    
    //Check the bottom_right of (x,y).
    for(_x = x+1, _y = y+1; _x <= board->n_col() && _y <= board->n_row() && board->get_status(_x, _y) == Board::black_stone; _x++, _y++, point_b[3]++);
    for(; _x <= board->n_col() && _y <= board->n_row() && board->get_status(_x, _y) == Board::accessible; _x++, _y++, point_ba[3]++);
    for(; _x <= board->n_col() && _y <= board->n_row() && board->get_status(_x, _y) == Board::black_stone; _x++, _y++, point_bab[3]++);
    for(; _x <= board->n_col() && _y <= board->n_row() && board->get_status(_x, _y) == Board::accessible; _x++, _y++, point_baba[3]++);
    for(; _x <= board->n_col() && _y <= board->n_row() && board->get_status(_x, _y) == Board::black_stone; _x++, _y++, point_babab[3]++);
    
    //Check the bottom of (x,y).
    for(_y = y+1; _y <= board->n_row() && board->get_status(x, _y) == Board::black_stone; _y++, point_b[4]++);
    for(; _y <= board->n_row() && board->get_status(x, _y) == Board::accessible; _y++, point_ba[4]++);
    for(; _y <= board->n_row() && board->get_status(x, _y) == Board::black_stone; _y++, point_bab[4]++);
    for(; _y <= board->n_row() && board->get_status(x, _y) == Board::accessible; _y++, point_baba[4]++);
    for(; _y <= board->n_row() && board->get_status(x, _y) == Board::black_stone; _y++, point_babab[4]++);
    
    //Check the bottom-left of (x,y).
    for(_x = x-1, _y = y+1; _x >=1 && _y <= board->n_row() && board->get_status(_x, _y) == Board::black_stone; _x--, _y++, point_b[5]++);
    for(; _x >=1 && _y <= board->n_row() && board->get_status(_x, _y) == Board::accessible; _x--, _y++, point_ba[5]++);
    for(; _x >=1 && _y <= board->n_row() && board->get_status(_x, _y) == Board::black_stone; _x--, _y++, point_bab[5]++);
    for(; _x >=1 && _y <= board->n_row() && board->get_status(_x, _y) == Board::accessible; _x--, _y++, point_baba[5]++);
    for(; _x >=1 && _y <= board->n_row() && board->get_status(_x, _y) == Board::black_stone; _x--, _y++, point_babab[5]++);
    
    //Check the left of (x,y).
    for(_x = x-1; _x >=1 && board->get_status(_x, y) == Board::black_stone; _x++, point_b[6]++);
    for(; _x >=1 && board->get_status(_x, y) == Board::accessible; _x++, point_ba[6]++);
    for(; _x >=1 && board->get_status(_x, y) == Board::black_stone; _x++, point_bab[6]++);
    for(; _x >=1 && board->get_status(_x, y) == Board::accessible; _x++, point_baba[6]++);
    for(; _x >=1 && board->get_status(_x, y) == Board::black_stone; _x++, point_babab[6]++);
    
    //Check the top-left of (x,y).
    for(_x = x-1, _y = y-1; _x >= 1 && _y >=1 && board->get_status(_x, _y) == Board::black_stone; _x--, _y--, point_b[7]++);
    for(; _x >= 1 && _y >=1 && board->get_status(_x, _y) == Board::accessible; _x--, _y--, point_ba[7]++);
    for(; _x >= 1 && _y >=1 && board->get_status(_x, _y) == Board::black_stone; _x--, _y--, point_bab[7]++);
    for(; _x >= 1 && _y >=1 && board->get_status(_x, _y) == Board::accessible; _x--, _y--, point_baba[7]++);
    for(; _x >= 1 && _y >=1 && board->get_status(_x, _y) == Board::black_stone; _x--, _y--, point_babab[7]++);
    
    //End searching the chessboard.
    
    //If five black stones are connected, there is NO FORBIDDEN.
    for(unsigned i = 0; i < 4; i++)
    {
        if(point_b[i] + point_b[i+4] == 4)
            return NO_FORBIDDEN;
    }
    
    //Define two counters to count the number of the three-in-a-row and the four-in-a-row. Here the three-in-a-row not only means three black stones are connected, there are other conditions including "black-black-white-black", which may result in THREE-THREE FORBIDDEN. Similarly, the four-in-a-row also including "HUO SI" and "CHONG SI", which may contribute to FOUR-FOUR FORBIDDEN.
    int threecount = 0, fourcount = 0;
    
    //First of all, check LONG FORBIDDEN. If more than five black stones are connected, there is LONG FORBIDDEN.
    for(unsigned i = 0; i < 4; i++)
    {
        if(point_b[i] + point_b[i+4] >= 5)
            return LONG_FORBIDDEN;
        //If four black stones are connected, check whether it is the four-in-a-row.
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
        //If three black stones are connected, check whether there are the three-in-a-row or the four-in-a-row.
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
        //If two black stones are connected, check whether there are the three-in-a-row or the four-in-a-row.
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
        //If there is only one black stone, check whether there are the three-in-a-row or the four-in-a-row.
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
    
    //If there are more than one the four-in-a-row, there is FOUR-FOUR FORBIDDEN.
    if(fourcount > 1)
        return FOUR_FOUR_FORBIDDEN;
    //If there are more than one the three-in-a-row, there is THREE-THREE FORBIDDEN.
    if(threecount > 1)
        return THREE_THREE_FORBIDDEN;
    //If the two counters are both 1 or 0, there is NO FORBIDDEN, and the game will continue.
    return NO_FORBIDDEN;
}

//This function is designed to check whether the key point of the three-in-a-row and the four-in-a-row is the forbidden point, and return the result. It is a sub-function of the funtion ForbiddenCheck above.
static int KeyPointForbiddenCheck(Board *board, unsigned x, unsigned y, int point_b, int direction)
{
    //Define (i,j) as the coordinates of the key point.
    unsigned i, j;
    point_b++;
    if(direction >= 4)
        point_b = -point_b;
    //Calculate the coordinates of the key point.
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

//Check every point of the present chessboard and store all of the forbidden points in the vector "forbidden_points".
ForbiddenJudge::CurrentWinLoss ForbiddenJudge::judge()
{
    //Define coord to store the coordinates of the forbidden points.
    std::vector<unsigned> coord;
    
    //Search every point on the chessboard by i and j.
    for(unsigned i = 1; i <= board->n_col(); i++)
    {
        for(unsigned j=1; j <= board->n_row(); j++)
        {
            //Check whether the recent moved black stone is put at the forbidden point in the vector "forbidden_points", and if yes, the white wins.
            if(board->get_status(coord[0], coord[1]) == Board::black_stone)
                return white_wins;
            //If not, the vector "forbidden_points" is updated and the game goes on.
            if(ForbiddenCheck(board, i, j) == LONG_FORBIDDEN || ForbiddenCheck(board, i, j) == FOUR_FOUR_FORBIDDEN || ForbiddenCheck(board, i, j) == THREE_THREE_FORBIDDEN)
                forbidden_points.push_back(coord);
            else if(ForbiddenCheck(board, i, j) == NO_FORBIDDEN)
                return ongoing;
        }
    }
    
    //Check whether five black stones or five white stones are connected by standard gomoku judge and get the game result.
    StandardGomokuJudge std_judge(board);
    return std_judge.judge();
}

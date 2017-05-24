#include "winning_judge.h"

// Codes below are rather dirty. Are you sure to continue?
// Help your self fold these scopes!
FreeStyleJudge::GameStatus FreeStyleJudge::judge()
{
    if(n_in_row > board->n_row() && n_in_row > board->n_col())
        return ongoing;

    // First stage: judge the rows
    for(unsigned j = 1; j <= board->n_row(); j++)
    {
        unsigned in_row_black = 1, in_row_white = 1;
        for(unsigned i = 1; i < board->n_col(); i++)
        {
            if(board->get_status(i, j) == Board::black_stone
            && board->get_status(i + 1, j) == Board::black_stone)
                in_row_black++;
            else in_row_black = 1;
            if(in_row_black == n_in_row)    // Meet a five-in-row
            {
                // Set the marker!
                marker1_x = i + 2 - n_in_row; marker1_y = j;
                marker2_x = i + 1; marker2_y = j;
                // And return that the black wins!
                return black_wins;
            }
            if(board->get_status(i, j) == Board::white_stone
            && board->get_status(i + 1, j) == Board::white_stone)
                in_row_white++;
            else in_row_white = 1;
            if(in_row_white == n_in_row)
            {
                marker1_x = i + 2 - n_in_row; marker1_y = j;
                marker2_x = i + 1; marker2_y = j;
                return white_wins;
            }
        }
    }

    // Second stage: judge the columns
    for(unsigned i = 1; i <= board->n_col(); i++)
    {
        unsigned in_row_black = 1, in_row_white = 1;
        for(unsigned j = 1; j < board->n_row(); j++)
        {
            if(board->get_status(i, j) == Board::black_stone
            && board->get_status(i, j + 1) == Board::black_stone)
                in_row_black++;
            else in_row_black = 1;
            if(in_row_black == n_in_row)
            {
                marker1_x = i; marker1_y = j + 2 - n_in_row;
                marker2_x = i; marker2_y = j + 1;
                return black_wins;
            }
            if(board->get_status(i, j) == Board::white_stone
            && board->get_status(i, j + 1) == Board::white_stone)
                in_row_white++;
            else in_row_white = 1;
            if(in_row_white == n_in_row)
            {
                marker1_x = i; marker1_y = j + 2 - n_in_row;
                marker2_x = i; marker2_y = j + 1;
                return white_wins;
            }
        }
    }

    // Third stage: i j increasing direction
    for(unsigned i = 1; i <= board->n_col() - n_in_row + 1; i++)
    {
        unsigned in_row_black = 1, in_row_white = 1;
        for(unsigned j = 1; j < board->n_row() && i + j <= board->n_col(); j++)
        {
            if(board->get_status(i + j - 1, j) == Board::black_stone
            && board->get_status(i + j, j + 1) == Board::black_stone)
                in_row_black++;
            else in_row_black = 1;
            if(in_row_black == n_in_row)
            {
                marker1_x = i + j + 1 - n_in_row; marker1_y = j + 2 - n_in_row;
                marker2_x = i + j; marker2_y = j + 1;
                return black_wins;
            }
            if(board->get_status(i + j - 1, j) == Board::white_stone
            && board->get_status(i + j, j + 1) == Board::white_stone)
                in_row_white++;
            else in_row_white = 1;
            if(in_row_white == n_in_row)
            {
                marker1_x = i + j + 1 - n_in_row; marker1_y = j + 2 - n_in_row;
                marker2_x = i + j; marker2_y = j + 1;
                return white_wins;
            }
        }
    }
    for(unsigned j = 1; j <= board->n_row() - n_in_row + 1; j++)
    {
        unsigned in_row_black = 1, in_row_white = 1;
        for(unsigned i = 1; i < board->n_col() && i + j <= board->n_row(); i++)
        {
            if(board->get_status(i, j + i - 1) == Board::black_stone
            && board->get_status(i + 1, j + i) == Board::black_stone)
                in_row_black++;
            else in_row_black = 1;
            if(in_row_black == n_in_row)
            {
                marker1_x = i + 2 - n_in_row; marker1_y = i + j + 1 - n_in_row;
                marker2_x = i + 1; marker2_y = i + j;
                return black_wins;
            }
            if(board->get_status(i, j + i - 1) == Board::white_stone
            && board->get_status(i + 1, j + i) == Board::white_stone)
                in_row_white++;
            else in_row_white = 1;
            if(in_row_white == n_in_row)
            {
                marker1_x = i + 2 - n_in_row; marker1_y = i + j + 1 - n_in_row;
                marker2_x = i + 1; marker2_y = i + j;
                return white_wins;
            }
        }
    }

    // Fourth stage: i increasing j decreasing direction
    for(unsigned i = n_in_row; i <= board->n_col(); i++)
    {
        unsigned in_row_black = 1, in_row_white = 1;
        for(unsigned j = 1; j < board->n_row() && i - j <= board->n_col(); j++)
        {
            if(board->get_status(i - j + 1, j) == Board::black_stone
            && board->get_status(i - j, j + 1) == Board::black_stone)
                in_row_black++;
            else in_row_black = 1;
            if(in_row_black == n_in_row)
            {
                marker1_x = i - j + n_in_row - 1; marker1_y = j + 2 - n_in_row;
                marker2_x = i - j; marker2_y = j + 1;
                return black_wins;
            }
            if(board->get_status(i - j + 1, j) == Board::white_stone
            && board->get_status(i - j, j + 1) == Board::white_stone)
                in_row_white++;
            else in_row_white = 1;
            if(in_row_white == n_in_row)
            {
                marker1_x = i - j + n_in_row - 1; marker1_y = j + 2 - n_in_row;
                marker2_x = i - j; marker2_y = j + 1;
                return white_wins;
            }
        }
    }
    for(unsigned j = 1; j <= board->n_row() - n_in_row + 1; j++)
    {
        unsigned in_row_black = 1, in_row_white = 1;
        for(unsigned i = board->n_col(); i > 1 && j + board->n_col() - i + 1 <= board->n_row(); i--)
        {
            if(board->get_status(i, j + board->n_col() - i) == Board::black_stone
            && board->get_status(i - 1, j + board->n_col() - i + 1) == Board::black_stone)
                in_row_black++;
            else in_row_black = 1;
            if(in_row_black == n_in_row)
            {
                marker1_x = i - 1; marker1_y = j + board->n_col() - i + 1;
                marker2_x = i - 2 + n_in_row;
                marker2_y = j + board->n_col() - i + 2 - n_in_row;
                return black_wins;
            }
            if(board->get_status(i, j + board->n_col() - i) == Board::white_stone
            && board->get_status(i - 1, j + board->n_col() - i + 1) == Board::white_stone)
                in_row_white++;
            else in_row_white = 1;
            if(in_row_white == n_in_row)
            {
                marker1_x = i - 1; marker1_y = j + board->n_col() - i + 1;
                marker2_x = i - 2 + n_in_row;
                marker2_y = j + board->n_col() - i + 2 - n_in_row;
                return white_wins;
            }
        }
    }

    return ongoing;
}

StandardGomokuJudge::GameStatus StandardGomokuJudge::judge()
{
    if(n_in_row > board->n_row() && n_in_row > board->n_col())
        return ongoing;

    // First stage: judge the rows
    for(unsigned j = 1; j <= board->n_row(); j++)
    {
        unsigned in_row_black = 1, in_row_white = 1;
        unsigned max_in_row_black = 1, max_in_row_white = 1;
        unsigned temp_marker1_x = undef, temp_marker1_y = undef;
        unsigned temp_marker2_x = undef, temp_marker2_y = undef;
        for(unsigned i = 1; i < board->n_col(); i++)
        {
            if(board->get_status(i, j) == Board::black_stone
            && board->get_status(i + 1, j) == Board::black_stone)
                in_row_black++;
            else
            {
                max_in_row_black = in_row_black > max_in_row_black ? 
                    in_row_black : max_in_row_black;
                in_row_black = 1;
            }
            if(in_row_black == n_in_row)    // Meet a five-in-row
            {
                // Set the markers!
                temp_marker1_x = i + 2 - n_in_row; temp_marker1_y = j;
                temp_marker2_x = i + 1; temp_marker2_y = j;
            }
            if(board->get_status(i, j) == Board::white_stone
            && board->get_status(i + 1, j) == Board::white_stone)
                in_row_white++;
            else
            {
                max_in_row_white = in_row_white > max_in_row_white ?
                    in_row_white : max_in_row_white;
                in_row_white = 1;
            }
            if(in_row_white == n_in_row)
            {
                temp_marker1_x = i + 2 - n_in_row; temp_marker1_y = j;
                temp_marker2_x = i + 1; temp_marker2_y = j;
            }
        }
        if(max_in_row_black == n_in_row)
        {
            marker1_x = temp_marker1_x; marker1_y = temp_marker1_y;
            marker2_x = temp_marker2_x; marker2_y = temp_marker2_y;
            return black_wins;
        }
        if(max_in_row_white == n_in_row)
        {
            marker1_x = temp_marker1_x; marker1_y = temp_marker1_y;
            marker2_x = temp_marker2_x; marker2_y = temp_marker2_y;
            return white_wins;
        }
    }

    // Second stage: judge the columns
    for(unsigned i = 1; i <= board->n_col(); i++)
    {
        unsigned in_row_black = 1, in_row_white = 1;
        unsigned max_in_row_black = 1, max_in_row_white = 1;
        unsigned temp_marker1_x = undef, temp_marker1_y = undef;
        unsigned temp_marker2_x = undef, temp_marker2_y = undef;
        for(unsigned j = 1; j < board->n_row(); j++)
        {
            if(board->get_status(i, j) == Board::black_stone
            && board->get_status(i, j + 1) == Board::black_stone)
                in_row_black++;
            else
            {
                max_in_row_black = in_row_black > max_in_row_black ?
                    in_row_black : max_in_row_black;
                in_row_black = 1;
            }
            if(in_row_black == n_in_row)
            {
                marker1_x = i; marker1_y = j + 2 - n_in_row;
                marker2_x = i; marker2_y = j + 1;
            }
            if(board->get_status(i, j) == Board::white_stone
            && board->get_status(i, j + 1) == Board::white_stone)
                in_row_white++;
            else
            {
                max_in_row_white = in_row_white > max_in_row_white ?
                    in_row_white : max_in_row_white;
                in_row_white = 1;
            }
            if(in_row_white == n_in_row)
            {
                marker1_x = i; marker1_y = j + 2 - n_in_row;
                marker2_x = i; marker2_y = j + 1;
            }
        }
        if(max_in_row_black == n_in_row)
        {
            marker1_x = temp_marker1_x; marker1_y = temp_marker1_y;
            marker2_x = temp_marker2_x; marker2_y = temp_marker2_y;
            return black_wins;
        }
        if(max_in_row_white == n_in_row)
        {
            marker1_x = temp_marker1_x; marker1_y = temp_marker1_y;
            marker2_x = temp_marker2_x; marker2_y = temp_marker2_y;
            return white_wins;
        }
    }

    // Third stage: i j increasing direction
    for(unsigned i = 1; i <= board->n_col() - n_in_row + 1; i++)
    {
        unsigned in_row_black = 1, in_row_white = 1;
        unsigned max_in_row_black = 1, max_in_row_white = 1;
        unsigned temp_marker1_x = undef, temp_marker1_y = undef;
        unsigned temp_marker2_x = undef, temp_marker2_y = undef;
        for(unsigned j = 1; j < board->n_row() && i + j <= board->n_col(); j++)
        {
            if(board->get_status(i + j - 1, j) == Board::black_stone
            && board->get_status(i + j, j + 1) == Board::black_stone)
                in_row_black++;
            else
            {
                max_in_row_black = in_row_black > max_in_row_black ?
                    in_row_black : max_in_row_black;
                in_row_black = 1;
            }
            if(in_row_black == n_in_row)
            {
                temp_marker1_x = i + j + 1 - n_in_row; temp_marker1_y = j + 2 - n_in_row;
                temp_marker2_x = i + j; temp_marker2_y = j + 1;
            }
            if(board->get_status(i + j - 1, j) == Board::white_stone
            && board->get_status(i + j, j + 1) == Board::white_stone)
                in_row_white++;
            else
            {
                max_in_row_white = in_row_white > max_in_row_white ?
                    in_row_white : max_in_row_white;
                in_row_white = 1;
            }
            if(in_row_white == n_in_row)
            {
                temp_marker1_x = i + j + 1 - n_in_row; temp_marker1_y = j + 2 - n_in_row;
                temp_marker2_x = i + j; temp_marker2_y = j + 1;
            }
        }
        if(max_in_row_black == n_in_row)
        {
            marker1_x = temp_marker1_x; marker1_y = temp_marker1_y;
            marker2_x = temp_marker2_x; marker2_y = temp_marker2_y;
            return black_wins;
        }
        if(max_in_row_white == n_in_row)
        {
            marker1_x = temp_marker1_x; marker1_y = temp_marker1_y;
            marker2_x = temp_marker2_x; marker2_y = temp_marker2_y;
            return white_wins;
        }
    }
    for(unsigned j = 1; j <= board->n_row() - n_in_row + 1; j++)
    {
        unsigned in_row_black = 1, in_row_white = 1;
        unsigned max_in_row_black = 1, max_in_row_white = 1;
        unsigned temp_marker1_x = undef, temp_marker1_y = undef;
        unsigned temp_marker2_x = undef, temp_marker2_y = undef;
        for(unsigned i = 1; i < board->n_col() && i + j <= board->n_row(); i++)
        {
            if(board->get_status(i, j + i - 1) == Board::black_stone
            && board->get_status(i + 1, j + i) == Board::black_stone)
                in_row_black++;
            else
            {
                max_in_row_black = in_row_black > max_in_row_black ?
                    in_row_black : max_in_row_black;
                in_row_black = 1;
            }
            if(in_row_black == n_in_row)
            {
                temp_marker1_x = i + 2 - n_in_row; temp_marker1_y = i + j + 1 - n_in_row;
                temp_marker2_x = i + 1; temp_marker2_y = i + j;
            }
            if(board->get_status(i, j + i - 1) == Board::white_stone
            && board->get_status(i + 1, j + i) == Board::white_stone)
                in_row_white++;
            else
            {
                max_in_row_white = in_row_white > max_in_row_white ?
                    in_row_white : max_in_row_white;
                in_row_white = 1;
            }
            if(in_row_white == n_in_row)
            {
                temp_marker1_x = i + 2 - n_in_row; temp_marker1_y = i + j + 1 - n_in_row;
                temp_marker2_x = i + 1; temp_marker2_y = i + j;
            }
        }
        if(max_in_row_black == n_in_row)
        {
            marker1_x = temp_marker1_x; marker1_y = temp_marker1_y;
            marker2_x = temp_marker2_x; marker2_y = temp_marker2_y;
            return black_wins;
        }
        if(max_in_row_white == n_in_row)
        {
            marker1_x = temp_marker1_x; marker1_y = temp_marker1_y;
            marker2_x = temp_marker2_y; marker2_y = temp_marker2_y;
            return white_wins;
        }
    }

    // Fourth stage: i increasing j decreasing direction
    for(unsigned i = n_in_row; i <= board->n_col(); i++)
    {
        unsigned in_row_black = 1, in_row_white = 1;
        unsigned max_in_row_black = 1, max_in_row_white = 1;
        unsigned temp_marker1_x = undef, temp_marker1_y = undef;
        unsigned temp_marker2_x = undef, temp_marker2_y = undef;
        for(unsigned j = 1; j < board->n_row() && i - j <= board->n_col(); j++)
        {
            if(board->get_status(i - j + 1, j) == Board::black_stone
            && board->get_status(i - j, j + 1) == Board::black_stone)
                in_row_black++;
            else
            {
                max_in_row_black = in_row_black > max_in_row_black ?
                    in_row_black : max_in_row_black;
                in_row_black = 1;
            }
            if(in_row_black == n_in_row)
            {
                temp_marker1_x = i - j + n_in_row - 1; temp_marker1_y = j + 2 - n_in_row;
                temp_marker2_x = i - j; temp_marker2_y = j + 1;
            }
            if(board->get_status(i - j + 1, j) == Board::white_stone
            && board->get_status(i - j, j + 1) == Board::white_stone)
                in_row_white++;
            else
            {
                max_in_row_white = in_row_white > max_in_row_white ?
                    in_row_white : max_in_row_white;
                in_row_white = 1;
            }
            if(in_row_white == n_in_row)
            {
                temp_marker1_x = i - j + n_in_row - 1; temp_marker1_y = j + 2 - n_in_row;
                temp_marker2_x = i - j; temp_marker2_y = j + 1;
            }
        }
        if(max_in_row_black == n_in_row)
        {
            marker1_x = temp_marker1_x; marker1_y = temp_marker1_y;
            marker2_x = temp_marker2_x; marker2_y = temp_marker2_y;
            return black_wins;
        }
        if(max_in_row_white == n_in_row)
        {
            marker1_x = temp_marker1_x; marker1_y = temp_marker1_y;
            marker2_x = temp_marker2_x; marker2_y = temp_marker2_y;
            return white_wins;
        }
    }
    for(unsigned j = 1; j <= board->n_row() - n_in_row + 1; j++)
    {
        unsigned in_row_black = 1, in_row_white = 1;
        unsigned max_in_row_black = 1, max_in_row_white = 1;
        unsigned temp_marker1_x = undef, temp_marker1_y = undef;
        unsigned temp_marker2_x = undef, temp_marker2_y = undef;
        for(unsigned i = board->n_col(); i > 1 && j + board->n_col() - i + 1 <= board->n_row(); i--)
        {
            if(board->get_status(i, j + board->n_col() - i) == Board::black_stone
            && board->get_status(i - 1, j + board->n_col() - i + 1) == Board::black_stone)
                in_row_black++;
            else
            {
                max_in_row_black = in_row_black > max_in_row_black ?
                    in_row_black : max_in_row_black;
                in_row_black = 1;
            }
            if(in_row_black == n_in_row)
            {
                temp_marker1_x = i - 1; temp_marker1_y = j + board->n_col() - i + 1;
                temp_marker2_x = i - 2 + n_in_row;
                temp_marker2_y = j + board->n_col() - i + 2 - n_in_row;
            }
            if(board->get_status(i, j + board->n_col() - i) == Board::white_stone
            && board->get_status(i - 1, j + board->n_col() - i + 1) == Board::white_stone)
                in_row_white++;
            else
            {
                max_in_row_white = in_row_white > max_in_row_white ?
                    in_row_white : max_in_row_white;
                in_row_white = 1;
            }
            if(in_row_white == n_in_row)
            {
                temp_marker1_x = i - 1; temp_marker1_y = j + board->n_col() - i + 1;
                temp_marker2_x = i - 2 + n_in_row;
                temp_marker2_y = j + board->n_col() - i + 2 - n_in_row;
            }
        }
        if(max_in_row_black == n_in_row)
        {
            marker1_x = temp_marker1_x; marker1_y = temp_marker1_y;
            marker2_x = temp_marker2_x; marker2_y = temp_marker2_y;
            return black_wins;
        }
        if(max_in_row_white == n_in_row)
        {
            marker1_x = temp_marker1_x; marker1_y = temp_marker1_y;
            marker2_x = temp_marker2_x; marker2_y = temp_marker2_y;
            return white_wins;
        }
    }

    return ongoing;
}
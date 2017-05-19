// Implementation of the board
#include "board.h"

Board::Board(unsigned _n_rows, unsigned _n_cols,
    GameSettings *_global_game_settings)
{
    n_rows = _n_rows; n_cols = _n_cols; n_te = 0;
    board_data = new unsigned[(_n_rows + 1) * (_n_cols + 1)];
    for(unsigned i = 0; i < (n_rows+1)*(n_cols+1); i++)
        board_data[i] = accessible;
    game_settings = _global_game_settings;
    using_global_settings = true;
    if(game_settings == NULL)
    {
        using_global_settings = false;
        game_settings = new GameSettings();
    }
    marker1_x = undef; marker1_y = undef;
    marker2_x = undef; marker2_y = undef;
    n_in_row = 5;
    return;
}

Board::~Board()
{
    delete board_data;
    return;
}

Board::Board(const Board &src)
{
    n_rows = src.n_rows;
    n_cols = src.n_cols;
    n_te = src.n_te;
    board_data = new unsigned[(n_rows + 1) * (n_cols + 1)];
    for(unsigned i = 0; i < (n_rows+1)*(n_cols+1); i++)
        board_data[i] = src.board_data[i];
    game_sequence = src.game_sequence;
    game_settings = new GameSettings(src.game_settings);
    using_global_settings = false;
    marker1_x = src.marker1_x; marker1_y = src.marker1_y;
    marker2_x = src.marker2_x; marker2_y = src.marker2_y;
    n_in_row = src.n_in_row;
    return;
}

bool Board::set_global_settings(GameSettings *_game_settings)
{
    if(!_game_settings) return false;
    if(!using_global_settings)
    {
        delete game_settings;
        using_global_settings = true;
    }
    game_settings = _game_settings;
    return true;
}

bool Board::general_te(unsigned x, unsigned y, PosStatus stone)
{
    if(x == 0 || x > n_cols) return false;
    if(y == 0 || y > n_rows) return false;
    if(get_status(x, y) != accessible) return false; 
    // Construct a new te object
    Te new_te(x, y,
        stone == black_stone ? Te::black : Te::white,
        ++n_te,
        Te::te);
    // Move on the board
    board_data[x + y*n_cols] = stone;
    // Push in the game sequence stack
    game_sequence.push_back(new_te);
    return true;
}

bool Board::general_remove(unsigned x, unsigned y, PosStatus stone)
{
    if(x == 0 || x > n_cols) return false;
    if(y == 0 || y > n_rows) return false;
    if(get_status(x, y) == accessible) return false;
    Te new_te(x, y,
        stone == black_stone ? Te::black : Te::white,
        n_te,
        Te::remove);
    board_data[x + y*n_cols] = accessible;
    game_sequence.push_back(new_te);
    return true;
}

bool Board::black_te(unsigned x, unsigned y)
{return general_te(x, y, black_stone);}
bool Board::white_te(unsigned x, unsigned y)
{return general_te(x, y, white_stone);}
bool Board::black_remove(unsigned x, unsigned y)
{return general_remove(x, y, black_stone);}
bool Board::white_remove(unsigned x, unsigned y)
{return general_remove(x, y, white_stone);}

Board::PosStatus Board::get_status(unsigned x, unsigned y) const
{
    if(x == 0 || x > n_cols) return undefined;
    if(y == 0 || y > n_rows) return undefined;
    return board_data[x + y*n_cols];
}

// ============= To do: to be fully implemented! ==============

Board::GameStatus Board::judge()
{
    return free_style_judge();
}

Board::GameStatus Board::free_style_judge()
{
    if(n_in_row > n_rows && n_in_row > n_cols) return ongoing;

    // First stage: judge the rows
    for(unsigned j = 1; j <= n_rows; j++)
    {
        unsigned in_row_black = 1, in_row_white = 1;
        for(unsigned i = 1; i < n_cols; i++)
        {
            if(get_status(i, j) == black_stone
            && get_status(i + 1, j) == black_stone)
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
            if(get_status(i, j) == white_stone
            && get_status(i + 1, j) == white_stone)
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
    for(unsigned i = 1; i <= n_cols; i++)
    {
        unsigned in_row_black = 1, in_row_white = 1;
        for(unsigned j = 1; j < n_rows; j++)
        {
            if(get_status(i, j) == black_stone
            && get_status(i, j + 1) == black_stone)
                in_row_black++;
            else in_row_black = 1;
            if(in_row_black == n_in_row)
            {
                marker1_x = i; marker1_y = j + 2 - n_in_row;
                marker2_x = i; marker2_y = j + 1;
                return black_wins;
            }
            if(get_status(i, j) == white_stone
            && get_status(i, j + 1) == white_stone)
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
    for(unsigned i = 1; i <= n_cols - n_in_row + 1; i++)
    {
        unsigned in_row_black = 1, in_row_white = 1;
        for(unsigned j = 1; j < n_rows && i + j <= n_cols; j++)
        {
            if(get_status(i + j - 1, j) == black_stone
            && get_status(i + j, j + 1) == black_stone)
                in_row_black++;
            else in_row_black = 1;
            if(in_row_black == n_in_row)
            {
                marker1_x = i + j + 1 - n_in_row; marker1_y = j + 2 - n_in_row;
                marker2_x = i + j; marker2_y = j + 1;
                return black_wins;
            }
            if(get_status(i + j - 1, j) == white_stone
            && get_status(i + j, j + 1) == white_stone)
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
    for(unsigned j = 1; j <= n_rows - n_in_row + 1; j++)
    {
        unsigned in_row_black = 1, in_row_white = 1;
        for(unsigned i = 1; i < n_cols && i + j <= n_rows; i++)
        {
            if(get_status(i, j + i - 1) == black_stone
            && get_status(i + 1, j + i) == black_stone)
                in_row_black++;
            else in_row_black = 1;
            if(in_row_black == n_in_row)
            {
                marker1_x = i + 2 - n_in_row; marker1_y = i + j + 1 - n_in_row;
                marker2_x = i + 1; marker2_y = i + j;
                return black_wins;
            }
            if(get_status(i, j + i - 1) == white_stone
            && get_status(i + 1, j + i) == white_stone)
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
    for(unsigned i = n_in_row; i <= n_cols; i++)
    {
        unsigned in_row_black = 1, in_row_white = 1;
        for(unsigned j = 1; j < n_rows && i - j <= n_cols; j++)
        {
            if(get_status(i - j + 1, j) == black_stone
            && get_status(i - j, j + 1) == black_stone)
                in_row_black++;
            else in_row_black = 1;
            if(in_row_black == n_in_row)
            {
                marker1_x = i - j + n_in_row - 1; marker1_y = j + 2 - n_in_row;
                marker2_x = i - j; marker2_y = j + 1;
                return black_wins;
            }
            if(get_status(i - j + 1, j) == white_stone
            && get_status(i - j, j + 1) == white_stone)
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
    for(unsigned j = 1; j <= n_rows - n_in_row + 1; j++)
    {
        unsigned in_row_black = 1, in_row_white = 1;
        for(unsigned i = n_cols; i > 1 && j + n_cols - i + 1 <= n_rows; i--)
        {
            if(get_status(i, j + n_cols - i) == black_stone
            && get_status(i - 1, j + n_cols - i + 1) == black_stone)
                in_row_black++;
            else in_row_black = 1;
            if(in_row_black == n_in_row)
            {
                marker1_x = i - 1; marker1_y = j + n_cols - i + 1;
                marker2_x = i - 2 + n_in_row;
                marker2_y = j + n_cols - i + 2 - n_in_row;
                return black_wins;
            }
            if(get_status(i, j + n_cols - i) == white_stone
            && get_status(i - 1, j + n_cols - i + 1) == white_stone)
                in_row_white++;
            else in_row_white = 1;
            if(in_row_white == n_in_row)
            {
                marker1_x = i - 1; marker1_y = j + n_cols - i + 1;
                marker2_x = i - 2 + n_in_row;
                marker2_y = j + n_cols - i + 2 - n_in_row;
                return white_wins;
            }
        }
    }

    return ongoing;
}

// ==================== To do: to be modified ============================
Board::GameStatus Board::standard_judge()
{
    if(n_in_row > n_rows && n_in_row > n_cols) return ongoing;

    // First stage: judge the rows
    for(unsigned j = 1; j <= n_rows; j++)
    {
        unsigned in_row_black = 1, in_row_white = 1;
        for(unsigned i = 1; i < n_cols; i++)
        {
            if(get_status(i, j) == black_stone
            && get_status(i + 1, j) == black_stone)
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
            if(get_status(i, j) == white_stone
            && get_status(i + 1, j) == white_stone)
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
    for(unsigned i = 1; i <= n_cols; i++)
    {
        unsigned in_row_black = 1, in_row_white = 1;
        for(unsigned j = 1; j < n_rows; j++)
        {
            if(get_status(i, j) == black_stone
            && get_status(i, j + 1) == black_stone)
                in_row_black++;
            else in_row_black = 1;
            if(in_row_black == n_in_row)
            {
                marker1_x = i; marker1_y = j + 2 - n_in_row;
                marker2_x = i; marker2_y = j + 1;
                return black_wins;
            }
            if(get_status(i, j) == white_stone
            && get_status(i, j + 1) == white_stone)
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
    for(unsigned i = 1; i <= n_cols - n_in_row + 1; i++)
    {
        unsigned in_row_black = 1, in_row_white = 1;
        for(unsigned j = 1; j < n_rows && i + j <= n_cols; j++)
        {
            if(get_status(i + j - 1, j) == black_stone
            && get_status(i + j, j + 1) == black_stone)
                in_row_black++;
            else in_row_black = 1;
            if(in_row_black == n_in_row)
            {
                marker1_x = i + j + 1 - n_in_row; marker1_y = j + 2 - n_in_row;
                marker2_x = i + j; marker2_y = j + 1;
                return black_wins;
            }
            if(get_status(i + j - 1, j) == white_stone
            && get_status(i + j, j + 1) == white_stone)
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
    for(unsigned j = 1; j <= n_rows - n_in_row + 1; j++)
    {
        unsigned in_row_black = 1, in_row_white = 1;
        for(unsigned i = 1; i < n_cols && i + j <= n_rows; i++)
        {
            if(get_status(i, j + i - 1) == black_stone
            && get_status(i + 1, j + i) == black_stone)
                in_row_black++;
            else in_row_black = 1;
            if(in_row_black == n_in_row)
            {
                marker1_x = i + 2 - n_in_row; marker1_y = i + j + 1 - n_in_row;
                marker2_x = i + 1; marker2_y = i + j;
                return black_wins;
            }
            if(get_status(i, j + i - 1) == white_stone
            && get_status(i + 1, j + i) == white_stone)
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
    for(unsigned i = n_in_row; i <= n_cols; i++)
    {
        unsigned in_row_black = 1, in_row_white = 1;
        for(unsigned j = 1; j < n_rows && i - j <= n_cols; j++)
        {
            if(get_status(i - j + 1, j) == black_stone
            && get_status(i - j, j + 1) == black_stone)
                in_row_black++;
            else in_row_black = 1;
            if(in_row_black == n_in_row)
            {
                marker1_x = i - j + n_in_row - 1; marker1_y = j + 2 - n_in_row;
                marker2_x = i - j; marker2_y = j + 1;
                return black_wins;
            }
            if(get_status(i - j + 1, j) == white_stone
            && get_status(i - j, j + 1) == white_stone)
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
    for(unsigned j = 1; j <= n_rows - n_in_row + 1; j++)
    {
        unsigned in_row_black = 1, in_row_white = 1;
        for(unsigned i = n_cols; i > 1 && j + n_cols - i + 1 <= n_rows; i--)
        {
            if(get_status(i, j + n_cols - i) == black_stone
            && get_status(i - 1, j + n_cols - i + 1) == black_stone)
                in_row_black++;
            else in_row_black = 1;
            if(in_row_black == n_in_row)
            {
                marker1_x = i - 1; marker1_y = j + n_cols - i + 1;
                marker2_x = i - 2 + n_in_row;
                marker2_y = j + n_cols - i + 2 - n_in_row;
                return black_wins;
            }
            if(get_status(i, j + n_cols - i) == white_stone
            && get_status(i - 1, j + n_cols - i + 1) == white_stone)
                in_row_white++;
            else in_row_white = 1;
            if(in_row_white == n_in_row)
            {
                marker1_x = i - 1; marker1_y = j + n_cols - i + 1;
                marker2_x = i - 2 + n_in_row;
                marker2_y = j + n_cols - i + 2 - n_in_row;
                return white_wins;
            }
        }
    }

    return ongoing;
}
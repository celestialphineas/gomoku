// Implementation of the board
// Celestial Phineas @ ZJU
#include "board.h"

Board::Board(unsigned _n_rows, unsigned _n_cols)
{
    // Initialize the board data.
    n_rows = _n_rows; n_cols = _n_cols; max_id = 0;
    board_data = new unsigned[(_n_rows + 1) * (_n_cols + 1)];
    for(unsigned i = 0; i < (n_rows+1)*(n_cols+1); i++)
        board_data[i] = accessible;
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
    max_id = src.max_id;
    board_data = new unsigned[(n_rows + 1) * (n_cols + 1)];
    for(unsigned i = 0; i < (n_rows+1)*(n_cols+1); i++)
        board_data[i] = src.board_data[i];
    game_sequence = src.game_sequence;
    return;
}

bool Board::general_te(unsigned x, unsigned y, PosStatus stone)
{
    if(x == 0 || x > n_cols) return false;
    if(y == 0 || y > n_rows) return false;
    if(get_status(x, y) != accessible) return false;
    // Construct a new te object
    Te new_te(x, y, stone == black_stone ? Te::black : Te::white,
        ++max_id, Te::te);
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
    for(std::deque<Te>::iterator i = game_sequence.end();
        i != game_sequence.begin(); i--)
    {
        if(i->x() == x && i->y() == y)
        {
            i->set_id(0);    // 0 is a reserved value
            break;
        }
    }
    max_id = 0;
    for(std::deque<Te>::iterator i = game_sequence.begin();
        i != game_sequence.end(); i++)
            if(i->id() > max_id) max_id = i->id();
    Te new_te(x, y, stone == black_stone ? Te::black : Te::white,
        0, Te::remove);
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

bool Board::undo()
{
    if(game_sequence.empty()) return false;
    if(game_sequence.back().is_te())
    {
        unsigned undo_x = game_sequence.back().x();
        unsigned undo_y = game_sequence.back().y();
        if(game_sequence.back().id() == max_id)
            max_id--;
        board_data[undo_x + undo_y*n_cols] = accessible;
        game_sequence.pop_back();
        return true;
    }
    else
    {
        unsigned undo_x = game_sequence.back().x();
        unsigned undo_y = game_sequence.back().y();
        game_sequence.pop_back();
        for(std::deque<Te>::iterator i = game_sequence.end();
            i != game_sequence.begin(); i--)
        {
            if(i->x() == undo_x && i->y() == undo_y)
            {
                unsigned local_max_id = 0;
                for(std::deque<Te>::iterator j = game_sequence.begin();
                    j != i; j++)
                        if(j->id() > local_max_id) local_max_id = j->id();
                i->set_id(++local_max_id);
                board_data[undo_x + undo_y*n_cols]
                    = i->is_black() ? black_stone : white_stone;
                return true;
            }
        }
        return false;
    }
}

bool Board::empty() const
{
    if(game_sequence.empty()) return true;
    for(unsigned i = 1; i <= n_rows; i++)
    for(unsigned j = 1; j <= n_cols; j++)
    {
        if(get_status(i, j) != accessible) return false;
    }
    return true;
}

std::vector<Board::SelectedRow> Board::get_rows() const
{
    std::vector<SelectedRow> *result = new std::vector<SelectedRow>;
    for(unsigned j = 1; j <= n_rows; j++)
    {
        SelectedRow new_row;
        new_row.begin_x = 1; new_row.begin_y = j;
        for(unsigned i = 1; i <= n_cols; i++)
        {
            new_row.row_list.push_back(get_status(i, j));
        }
        result->push_back(new_row);
    }
    return *result;
}

std::vector<Board::SelectedRow> Board::get_cols() const
{
    std::vector<SelectedRow> *result = new std::vector<SelectedRow>;
    for(unsigned i = 1; i <= n_cols; i++)
    {
        SelectedRow new_col;
        new_col.begin_x = i; new_col.begin_y = 1;
        for(unsigned j = 1; j <= n_rows; j++)
        {
            new_col.row_list.push_back(get_status(i, j));
        }
        result->push_back(new_col);
    }
    return *result;
}

std::vector<Board::SelectedRow> Board::get_diags() const
{
    std::vector<SelectedRow> *result = new std::vector<SelectedRow>;
    for(unsigned i = 1; i <= n_cols; i++)
    {
        SelectedRow new_diag;
        new_diag.begin_x = i; new_diag.begin_y = 1;
        for(unsigned k = 0;
            i + k <= n_cols && 1 + k <= n_rows; k++)
        {
            new_diag.row_list.push_back(get_status(i + k, 1 + k));
        }
        result->push_back(new_diag);
    }
    for(unsigned j = 2; j <= n_rows; j++)
    {
        SelectedRow new_diag;
        new_diag.begin_x = 1; new_diag.begin_y = j;
        for(unsigned k = 0;
            1 + k <= n_cols && j + k <= n_cols; k++)
        {
            new_diag.row_list.push_back(get_status(1 + k, j + k));
        }
        result->push_back(new_diag);
    }
    return *result;
}

std::vector<Board::SelectedRow> Board::get_adiags() const
{
    std::vector<SelectedRow> *result = new std::vector<SelectedRow>;
    for(unsigned i = 1; i <= n_cols; i++)
    {
        SelectedRow new_adiag;
        new_adiag.begin_x = i; new_adiag.begin_y = 1;
        for(unsigned k = 0;
            i - k >= 1 && 1 + k <= n_rows; k++)
        {
            new_adiag.row_list.push_back(get_status(i - k, 1 + k));
        }
        result->push_back(new_adiag);
    }
    for(unsigned i = 2; i <= n_cols; i++)
    {
        SelectedRow new_adiag;
        new_adiag.begin_x = i; new_adiag.begin_y = n_rows;
        for(unsigned k = 0;
            i + k <= n_cols && n_rows - k >= 1; k++)
        {
            new_adiag.row_list.push_back(get_status(i + k, n_rows - k));
        }
        result->push_back(new_adiag);
    }
    return *result;
}
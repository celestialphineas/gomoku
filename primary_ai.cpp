#include "primary_ai.h"

static std::vector<std::vector<unsigned> > find_valid_pos(
    bool player_stone, const Board *board, const WinningJudge *judge)
{
    std::vector<std::vector<unsigned> > *te_candidates
        = new std::vector<std::vector<unsigned> >;
    for(unsigned i = 1; i <= board->n_col(); i++)
    for(unsigned j = 1; j <= board->n_row(); j++)
    {
        if(board->get_status(i, j) == Board::accessible)
        {
            Board temp_board(*board);
            if(player_stone == Player::black) temp_board.black_te(i, j);
            WinningJudge *temp_judge = judge->clone();
            temp_judge->set_board(&temp_board);
            if(temp_judge->judge() ==
                (player_stone ?
                    /* If use white, return */ WinningJudge::black_wins :
                    /* If use black, return */ WinningJudge::white_wins))
                        {delete temp_judge; continue;}
            else
            {
                std::vector<unsigned> coord;
                coord.push_back(i); coord.push_back(j);
                te_candidates->push_back(coord);
                delete temp_judge;
            }
        }
    }
    return *te_candidates;
}

bool PrimaryAI::te()
{
    if(board->full()) return false;
    if(board->empty())
    {
        if(stone_color == black)
            board->black_te((board->n_col() + 1)/2, (board->n_row() + 1)/2);
        else board->white_te((board->n_col() + 1)/2, (board->n_row() + 1)/2);
        return true;
    }
    // Find out all available positions and put them in a list
    std::vector<std::vector<unsigned> >
        te_candidates = find_valid_pos(stone_color, board, judge);
    // Handle an exception
    if(te_candidates.empty())
    {
        for(unsigned i = 1; i <= board->n_col(); i++)
        for(unsigned j = 1; j <= board->n_row(); j++)
        {
            if(board->get_status(i, j) == Board::accessible)
            {
                if(stone_color == white) {board->white_te(i, j); return true;}
                else {board->black_te(i, j); return true;}
            }
        }
    }
    // Find if there is an immediate threat
    // TODO!!!

    return true;
}

bool PrimaryAI::remove(const std::vector<Te> te_candidates)
{
    // TODO!!!
    if(te_candidates.size() == 0) return false;
    return true;
}
#include "primary_ai.h"
#include <algorithm>
#include <ctime>

static unsigned evaluate_board(const Board *board)
{
    static const unsigned median = 0xffffffff / 2;
    static const unsigned d_straight1 = 2;
    static const unsigned d_straight2 = 5;
    static const unsigned d_straight3 = 50;
    static const unsigned d_straight4 = 1000;
    static const unsigned d_blocked1 = 1;
    static const unsigned d_blocked2 = 4;
    static const unsigned d_blocked3 = 20;
    static const unsigned d_blocked4 = 500;

    unsigned value = median;
    ThreatFinder threat_finder(board);

    std::vector<ThreatFinder::Threat> *found;
    found = threat_finder.find_straight(ThreatFinder::black, 1);
    value -= found->size() * d_straight1;
    delete found;

    found = threat_finder.find_straight(ThreatFinder::black, 2);
    value -= found->size() * d_straight2;
    delete found;

    found = threat_finder.find_straight(ThreatFinder::black, 3);
    value -= found->size() * d_straight3;
    delete found;

    found = threat_finder.find_straight(ThreatFinder::black, 4);
    value -= found->size() * d_straight4;
    delete found;

    found = threat_finder.find_one_end_blocked(ThreatFinder::black, 1);
    value -= found->size() * d_blocked1;
    delete found;

    found = threat_finder.find_one_end_blocked(ThreatFinder::black, 2);
    value -= found->size() * d_blocked2;
    delete found;

    found = threat_finder.find_one_end_blocked(ThreatFinder::black, 3);
    value -= found->size() * d_blocked3;
    delete found;
    
    found = threat_finder.find_one_end_blocked(ThreatFinder::black, 4);
    value -= found->size() * d_blocked4;
    delete found;

    found = threat_finder.find_straight(ThreatFinder::white, 1);
    value += found->size() * d_straight1;
    delete found;

    found = threat_finder.find_straight(ThreatFinder::white, 2);
    value += found->size() * d_straight2;
    delete found;

    found = threat_finder.find_straight(ThreatFinder::white, 3);
    value += found->size() * d_straight3;
    delete found;

    found = threat_finder.find_straight(ThreatFinder::white, 4);
    value += found->size() * d_straight4;
    delete found;

    found = threat_finder.find_one_end_blocked(ThreatFinder::white, 1);
    value += found->size() * d_blocked1;
    delete found;

    found = threat_finder.find_one_end_blocked(ThreatFinder::white, 2);
    value += found->size() * d_blocked2;
    delete found;

    found = threat_finder.find_one_end_blocked(ThreatFinder::white, 3);
    value += found->size() * d_blocked3;
    delete found;

    found = threat_finder.find_one_end_blocked(ThreatFinder::white, 4);
    value += found->size() * d_blocked4;
    delete found; found = NULL;

    return value;
}

bool black_comp(std::vector<unsigned> a, std::vector<unsigned> b)
{if(a.size() < 3 || b.size() < 3) return true; return a[2] < b[2];}

bool white_comp(std::vector<unsigned> a, std::vector<unsigned> b)
{if(a.size() < 3 || b.size() < 3) return true; return a[2] > b[2];}

bool PrimaryAI::te()
{
    if(board->full()) return false;
    if(board->empty())
    {
        if(stone_color == black)
            board->black_te((board->n_col() + 1)/2, (board->n_row() + 1)/2);
        else
            board->white_te((board->n_col() + 1)/2, (board->n_row() + 1)/2);
        return true;
    }

    std::vector<std::vector<unsigned> > te_candidates;
    Board temp_board(*board);
    WinningJudge *temp_judge = judge->clone();
    temp_judge->set_board(&temp_board);

    for(unsigned i = 1; i <= temp_board.n_col(); i++)
    for(unsigned j = 1; j <= temp_board.n_row(); j++)
    {
        if(temp_board.get_status(i, j) != Board::accessible) continue;
        if(stone_color == black) temp_board.black_te(i, j);
        else temp_board.white_te(i, j);
        if(temp_judge->judge() ==
            (stone_color ? WinningJudge::black_wins : WinningJudge::white_wins))
                {temp_board.undo(); continue;}
        std::vector<unsigned> coord;
        coord.push_back(i); coord.push_back(j);
        te_candidates.push_back(coord);
        temp_board.undo();
    }
    if(te_candidates.empty())
    {
        for(unsigned i = 1; i <= board->n_col(); i++)
        for(unsigned j = 1; j <= board->n_row(); j++)
        {
            if(board->get_status(i, j) == Board::accessible)
            {
                if(stone_color == black)
                {
                    board->black_te(i, j);
                    delete temp_judge;
                    return true;
                }
                else
                {
                    board->white_te(i, j);
                    delete temp_judge;
                    return true;
                }
            }
        }
        return false;
    }

    // Find if there is a position to win
    for(std::vector<std::vector<unsigned> >::const_iterator
        i = te_candidates.begin(); i != te_candidates.end(); i++)
    {
        if(stone_color == black) temp_board.black_te((*i)[0], (*i)[1]);
        else temp_board.white_te((*i)[0], (*i)[1]);
        if(temp_judge->judge() == 
            (stone_color ? WinningJudge::white_wins : WinningJudge::black_wins))
        {
            delete temp_judge;
            if(stone_color == black) board->black_te((*i)[0], (*i)[1]);
            else board->white_te((*i)[0], (*i)[1]);
            return true;
        }
        temp_board.undo();
    }

    // Find the local optimal
    for(std::vector<std::vector<unsigned> >::iterator te = te_candidates.begin();
        te != te_candidates.end(); te++)
    {
        if(stone_color == black) temp_board.black_te((*te)[0], (*te)[1]);
        else temp_board.white_te((*te)[0], (*te)[1]);
        te->push_back(evaluate_board(&temp_board));
        temp_board.undo();
    }
    if(stone_color == black)
    {
        std::sort(te_candidates.begin(), te_candidates.end(), black_comp);
    }
    else
    {
        std::sort(te_candidates.begin(), te_candidates.end(), white_comp);
    }
    std::vector<std::vector<unsigned> > optimal_list;
    for(std::vector<std::vector<unsigned> >::iterator i = te_candidates.begin();
        i != te_candidates.end(); i++)
    {
        if((*i)[2] == te_candidates[0][2])
            optimal_list.push_back(*i);
    }
    srand(unsigned(time(0)));
    unsigned random_index = rand() % optimal_list.size();
    if(stone_color == black)
        board->black_te(te_candidates[random_index][0],
            te_candidates[random_index][1]);
    else
        board->white_te(te_candidates[random_index][0],
            te_candidates[random_index][1]);
    delete temp_judge;
    return true;
}

bool PrimaryAI::remove(const std::vector<Te> te_candidates)
{
    // TODO!!!
    if(te_candidates.size() == 0) return false;
    return true;
}
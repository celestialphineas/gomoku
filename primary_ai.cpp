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
    for(unsigned i = 1; i <= board->n_col(); i++)
    for(unsigned j = 1; j <= board->n_row(); j++)
    {
        if(board->get_status(i, j) != Board::accessible) continue;
        std::vector<unsigned> coord;
        coord.push_back(i); coord.push_back(j);
        te_candidates.push_back(coord);
    }

    // Get all the possible te
    Board temp_board(*board);
    WinningJudge *temp_judge = judge->clone();
    temp_judge->set_board(&temp_board);
    for(std::vector<std::vector<unsigned> >::iterator i = te_candidates.begin();
        i != te_candidates.end();)
    {
        if(stone_color == black) temp_board.black_te((*i)[0], (*i)[1]);
        else temp_board.white_te((*i)[0], (*i)[1]);
        WinningJudge::GameStatus current_status = temp_judge->judge();
        // If loses
        if(current_status ==
            (stone_color ? WinningJudge::black_wins : WinningJudge::white_wins))
        {
            if(te_candidates.size() > 1)
            {
                // Erase the losing element
                i = te_candidates.erase(i);
                temp_board.undo();
                continue;
            }
            else // Preserve the element if there is only one left
            {
                temp_board.undo();
                break;
            }
        }
        // If wins
        if(current_status ==
            (stone_color ? WinningJudge::white_wins : WinningJudge::black_wins))
        {
            delete temp_judge;
            if(stone_color == black) board->black_te((*i)[0], (*i)[1]);
            else board->white_te((*i)[0], (*i)[1]);
            return true;
        }
        temp_board.undo();
        i++;
    }

    if(stone_color == black)
        board->black_te(te_candidates.front()[0], te_candidates.front()[1]);
    else
        board->white_te(te_candidates.front()[0], te_candidates.front()[1]);

    return true;
}

bool PrimaryAI::remove(const std::vector<Te> te_candidates)
{
    // TODO!!!
    if(te_candidates.size() == 0) return false;
    return true;
}
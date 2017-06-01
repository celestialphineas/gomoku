#include "primary_ai.h"
#include <algorithm>
#include <ctime>

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
    value -= threat_finder.find_straight(ThreatFinder::black, 1).size()
            * d_straight1;
    value -= threat_finder.find_straight(ThreatFinder::black, 2).size()
            * d_straight2;
    value -= threat_finder.find_straight(ThreatFinder::black, 3).size()
            * d_straight3;
    value -= threat_finder.find_straight(ThreatFinder::black, 4).size()
            * d_straight4;
    value -= threat_finder.find_one_end_blocked(ThreatFinder::black, 1).size()
            * d_blocked1;
    value -= threat_finder.find_one_end_blocked(ThreatFinder::black, 2).size()
            * d_blocked2;
    value -= threat_finder.find_one_end_blocked(ThreatFinder::black, 3).size()
            * d_blocked3;
    value -= threat_finder.find_one_end_blocked(ThreatFinder::black, 4).size()
            * d_blocked4;
    value += threat_finder.find_straight(ThreatFinder::white, 1).size()
            * d_straight1;
    value += threat_finder.find_straight(ThreatFinder::white, 2).size()
            * d_straight2;
    value += threat_finder.find_straight(ThreatFinder::white, 3).size()
            * d_straight3;
    value += threat_finder.find_straight(ThreatFinder::white, 4).size()
            * d_straight4;
    value += threat_finder.find_one_end_blocked(ThreatFinder::white, 1).size()
            * d_blocked1;
    value += threat_finder.find_one_end_blocked(ThreatFinder::white, 2).size()
            * d_blocked2;
    value += threat_finder.find_one_end_blocked(ThreatFinder::white, 3).size()
            * d_blocked3;
    value += threat_finder.find_one_end_blocked(ThreatFinder::white, 4).size()
            * d_blocked4;
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
    // Find if there is a position to win
    for(std::vector<std::vector<unsigned> >::const_iterator
        i = te_candidates.begin(); i != te_candidates.end(); i++)
    {
        Board temp_board(*board);
        WinningJudge *temp_judge = judge->clone();
        temp_judge->set_board(&temp_board);
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
    }

    // Find if there is an immediate threat
    // Find straight 3 and one-end-blocked 4
    ThreatFinder threat_finder(board);
    std::vector<ThreatFinder::Threat> straight3
        = threat_finder.find_straight(!stone_color, 3);
    std::vector<ThreatFinder::Threat> blocked4
        = threat_finder.find_one_end_blocked(!stone_color, 4);
    std::vector<std::vector<unsigned> > key_pos;
    for(std::vector<ThreatFinder::Threat>::const_iterator
        i = straight3.begin(); i != straight3.end(); i++)
    {
        key_pos.push_back((i->key_pos_list)[0]);
        key_pos.push_back((i->key_pos_list)[1]);
    }
    for(std::vector<ThreatFinder::Threat>::const_iterator
        i = blocked4.begin(); i != blocked4.end(); i++)
            {key_pos.push_back((i->key_pos_list)[0]);}

    std::sort(key_pos.begin(), key_pos.end());
    // Deletion from the immediate threats
    std::vector<unsigned> repeated;
    for(std::vector<std::vector<unsigned> >::iterator i = key_pos.begin();
        i != key_pos.end() && i + 1 != key_pos.end(); i++)
    {
        if((*i) == *(i+1))
        {
            repeated = (*i);
            key_pos.erase(i + 1);
            i--;    // TAKE CARE!!!
        }
    }
    if(!repeated.empty())
    {
        if(stone_color == white) board->white_te(repeated[0], repeated[1]);
        else board->black_te(repeated[0], repeated[1]);
        return true;
    }
    te_candidates = key_pos;
    // TODO: Evaluate the most valueable te!
    for(std::vector<std::vector<unsigned> >::iterator te = te_candidates.begin();
        te != te_candidates.end(); te++)
    {
        Board temp_board(*board);
        if(stone_color == black) temp_board.black_te((*te)[0], (*te)[1]);
        else temp_board.white_te((*te)[0], (*te)[1]);
        te->push_back(evaluate_board(&temp_board));
    }
    if(stone_color == black)
    {
        std::sort(te_candidates.begin(), te_candidates.end(), black_comp);
        board->black_te(te_candidates[0][0], te_candidates[0][1]);
    }
    else
    {
        std::sort(te_candidates.begin(), te_candidates.end(), white_comp);
        board->white_te(te_candidates[0][0], te_candidates[0][1]);
    }

    return true;
}

bool PrimaryAI::remove(const std::vector<Te> te_candidates)
{
    // TODO!!!
    if(te_candidates.size() == 0) return false;
    return true;
}
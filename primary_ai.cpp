#include "primary_ai.h"
#include <algorithm>
#include <ctime>

static unsigned evaluate_board(const Board *board)
{
    static const unsigned median = 0xffffffff / 2;
    // static const unsigned d_straight1 = 1;
    static const unsigned d_straight2 = 5;
    static const unsigned d_straight3 = 500;
    static const unsigned d_straight4 = 1000;
    static const unsigned d_blocked1 = 2;
    static const unsigned d_blocked2 = 4;
    static const unsigned d_blocked3 = 20;
    static const unsigned d_blocked4 = 200;

    unsigned value = median;
    ThreatFinder threat_finder(board);

    std::vector<ThreatFinder::Threat> *found;
    // found = threat_finder.find_straight(ThreatFinder::black, 1);
    // value -= found->size() * d_straight1;
    // delete found;

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

    // found = threat_finder.find_straight(ThreatFinder::white, 1);
    // value += found->size() * d_straight1;
    // delete found;

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

static bool black_comp(std::vector<unsigned> a, std::vector<unsigned> b)
{if(a.size() < 3 || b.size() < 3) return true; return a[2] < b[2];}

static bool white_comp(std::vector<unsigned> a, std::vector<unsigned> b)
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

    // Find all the immediate threats
    ThreatFinder threat_finder(board);
    std::vector<ThreatFinder::Threat>* straight_threats
        = threat_finder.find_straight(!stone_color, 3);
    std::vector<ThreatFinder::Threat>* blocked_threats
        = threat_finder.find_one_end_blocked(!stone_color, 4);
    std::vector<std::vector<unsigned> > key_pos;
    // Gather the immediate threats
    for(std::vector<ThreatFinder::Threat>::iterator i = straight_threats->begin();
        i != straight_threats->end(); i++)
    {
        key_pos.insert(key_pos.end(), i->key_pos_list.begin(), i->key_pos_list.end());
    }
    for(std::vector<ThreatFinder::Threat>::iterator i = blocked_threats->begin();
        i != blocked_threats->end(); i++)
    {
        key_pos.insert(key_pos.end(), i->key_pos_list.begin(), i->key_pos_list.end());
    }
    delete straight_threats; delete blocked_threats;

    // Find the te candidates
    std::vector<std::vector<unsigned> > te_candidates;
    if(key_pos.empty())
        for(unsigned i = 1; i <= board->n_col(); i++)
        for(unsigned j = 1; j <= board->n_row(); j++)
    {
        std::deque<Te>* game_sequence = board->get_game_sequence();
        if(game_sequence->size() < 8)
        {
            delete game_sequence;
            if(i <= 5 || i > board->n_col() - 5
            || j <= 5 || j > board->n_row() - 5)
                {continue;}
        }
        if(board->get_status(i, j) != Board::accessible) continue;
        std::vector<unsigned> coord;
        coord.push_back(i); coord.push_back(j);
        te_candidates.push_back(coord);
    }
    else te_candidates = key_pos;

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

    for(std::vector<std::vector<unsigned> >::iterator i = te_candidates.begin();
        i != te_candidates.end(); i++)
    {
        if(stone_color == black) temp_board.black_te((*i)[0], (*i)[1]);
        else temp_board.white_te((*i)[0], (*i)[1]);
        unsigned board_value = evaluate_board(&temp_board);
        i->push_back(board_value);
        temp_board.undo();
    }

    if(stone_color == black)
        std::sort(te_candidates.begin(), te_candidates.end(), black_comp);
    else
        std::sort(te_candidates.begin(), te_candidates.end(), white_comp);

    unsigned count = 0;
    for(std::vector<std::vector<unsigned> >::iterator i = te_candidates.begin();
        i != te_candidates.end(); i++)
    {
        if((*i)[2] == te_candidates.front()[2]) count++;
    }
    srand(unsigned(time(0)));
    unsigned random_index = rand() % count;

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
    if(te_candidates.size() == 0) return false;
    Board temp_board(*board);
    WinningJudge *temp_judge = judge->clone();
    temp_judge->set_board(&temp_board);

    std::vector<Te>::const_iterator min_it;
    std::vector<Te>::const_iterator max_it;
    unsigned found_min = 0xffffffff, found_max = 0;
    for(std::vector<Te>::const_iterator i = te_candidates.begin();
        i != te_candidates.end(); i++)
    {
        if(stone_color == black) temp_board.black_remove(i->x(), i->y());
        else temp_board.white_remove(i->x(), i->y());
        unsigned board_value = evaluate_board(&temp_board);
        if(board_value <= found_min)
        {
            found_min = board_value;
            min_it = i;
        }
        if(board_value >= found_max)
        {
            found_max = board_value;
            max_it = i;
        }
        temp_board.undo();
    }
    if(stone_color == black) board->black_remove(min_it->x(), min_it->y());
    else board->white_remove(max_it->x(), max_it->y());

    delete temp_judge;
    return true;
}
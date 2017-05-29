#include "threat_finder.h"

// The logic is very similar to the judge
std::vector<Threat> &ThreatFinder::find_straight(bool who, unsigned n_to_check) const
{
    std::vector<Threat> *result = new std::vector<Threat>;
    // First stage: check the rows
    for(unsigned j = 1; j <= board->n_row(); j++)
    {
        unsigned i = 1;
        while(i < board->n_col() - n_to_check)
        {
            if(board->get_status(i, j) != Board::accessible)
                {i++; continue;}
            for(unsigned k = 1; k <= n_to_check; k++)
            {
                if(board->get_status(i + k, j)
                    != (who ? Board::white_stone : Board::black_stone))
                        goto next_loop1;
            }
            if(board->get_status(i + n_to_check + 1, j) == Board::accessible)
            // A threat spotted
            {
                Threat threat;
                threat.threat_src = who;
                threat.pos1_x = i + 1; threat.pos1_y = j;
                threat.pos2_x = i + n_to_check; threat.pos2_y = j;
                std::vector<unsigned> coord;
                coord.push_back(i); coord.push_back(j);
                threat.key_pos_list.push_back(coord);
                coord[0] = i + n_to_check + 1; coord[1] = j;
                threat.key_pos_list.push_back(coord);
                result->push_back(threat);
            }
            next_loop1: i++;
        }
    }
    // Second stage: check the columns
    for(unsigned i = 1; i <= board->n_col(); i++)
    {
        unsigned j = 1;
        while(j < board->n_row() - n_to_check)
        {
            if(board->get_status(i, j) != Board::accessible)
                {j++; continue;}
            for(unsigned k = 1; k <= n_to_check; k++)
            {
                if(board->get_status(i, j + k)
                    != (who ? Board::white_stone : Board::black_stone))
                        goto next_loop2;
            }
            if(board->get_status(i, j + n_to_check + 1) == Board::accessible)
            // A threat spotted
            {
                Threat threat;
                threat.threat_src = who;
                threat.pos1_x = i; threat.pos1_y = j + 1;
                threat.pos2_x = i; threat.pos2_y = j + n_to_check;
                std::vector<unsigned> coord;
                coord.push_back(i); coord.push_back(j);
                threat.key_pos_list.push_back(coord);
                coord[0] = i; coord[1] = j + n_to_check + 1;
                threat.key_pos_list.push_back(coord);
                result->push_back(threat);
            }
            next_loop2: j++;
        }
    }

    // TODO: to find the diagonals
    return *result;
}
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

    // Third stage: diagonal for x coordinate and y coordinate both increasing
    // direction
    for(int i = 1; i <= int(board->n_col()) - int(n_to_check); i++)
    // Diagonals from (i, 1) ...
    {
        int k = 0; // k is the increment
        while(k < int(board->n_row()) - int(n_to_check))
        {
            if(board->get_status(i + k, 1 + k) != Board::accessible)
                {k++; continue;}
            for(unsigned m = 1; m <= n_to_check; m++)
            {
                if(board->get_status(i + k + m, 1 + k + m)
                    != (who ? Board::white_stone : Board::black_stone))
                        goto next_loop3;
            }
            if(board->get_status(i + k + n_to_check + 1, k + n_to_check + 2)
                == Board::accessible) // A threat spotted
            {
                Threat threat;
                threat.threat_src = who;
                threat.pos1_x = i + k + 1; threat.pos1_y = 2 + k;
                threat.pos2_x = i + k + n_to_check;
                threat.pos2_y = 1 + k + n_to_check;
                std::vector<unsigned> coord;
                coord.push_back(i + k); coord.push_back(1 + k);
                threat.key_pos_list.push_back(coord);
                coord[0] = i + k + n_to_check + 1;
                coord[1] = k + n_to_check + 2;
                threat.key_pos_list.push_back(coord);
                result->push_back(threat);
            }
            next_loop3: k++;
        }
    }
    for(int j = 2; j <= int(board->n_row()) - int(n_to_check); j++)
    // Diagonals from (1, j)
    {
        int k = 0; // k is the increment
        while(k < int(board->n_col()) - int(n_to_check))
        {
            if(board->get_status(1 + k, j + k) != Board::accessible)
                {k++; continue;}
            for(unsigned m = 1; m <= n_to_check; m++)
            {
                if(board->get_status(1 + k + m, j + k + m)
                    != (who ? Board::white_stone : Board::black_stone))
                        goto next_loop4;
            }
            if(board->get_status(k + n_to_check + 2, j + k + n_to_check + 1)
                == Board::accessible) // A threat spotted
            {
                Threat threat;
                threat.threat_src = who;
                threat.pos1_x = k + 2; threat.pos1_y = j + k + 1;
                threat.pos2_x = 1 + k + n_to_check;
                threat.pos2_y = j + k + n_to_check;
                std::vector<unsigned> coord;
                coord.push_back(1 + k); coord.push_back(j + k);
                threat.key_pos_list.push_back(coord);
                coord[0] = k + n_to_check + 2;
                coord[1] = j + k + n_to_check + 1;
                threat.key_pos_list.push_back(coord);
                result->push_back(threat);
            }
            next_loop4: k++;
        }
    }

    // Fourth stage: No use to comment! QAQ ... kuku... No one else except me
    // would be here to see my comments! No one will notice!!
    for(int i = board->n_col(); i > int(n_to_check); i--)
    // Diagonals from (i, 1)
    {
        int k = 0; // k is the decrement
        while(k < int(board->n_row()) - int(n_to_check))
        {
            if(board->get_status(i - k, 1 + k)
                != Board::accessible)
                    {k++; continue;}
            for(unsigned m = 1; m <= n_to_check; m++)
            {
                if(board->get_status(i - k - m, 1 + k + m)
                    != (who ? Board::white_stone : Board::black_stone))
                        goto next_loop5;
            }
            if(board->get_status(i - k - n_to_check - 1,
                k + n_to_check + 2) == Board::accessible) // A threat spotted
            {
                Threat threat;
                threat.threat_src = who;
                threat.pos1_x = i - k - n_to_check;
                threat.pos1_y = 1 + k + n_to_check;
                threat.pos2_x = i - k - 1;
                threat.pos2_y = 2 + k;
                std::vector<unsigned> coord;
                coord.push_back(i - k - n_to_check - 1);
                coord.push_back(k + n_to_check + 2);
                threat.key_pos_list.push_back(coord);
                coord[0] = i - k; coord[1] = 1 + k;
                threat.key_pos_list.push_back(coord);
                result->push_back(threat);
            }
            next_loop5: k++;
        }
    }
    for(int j = 2; j < int(board->n_row()) - int(n_to_check); j++)
    // Diagonals from (n_cols, j)
    {
        int k = 0; // k is the decrement
        while(board->n_col() - k >= n_to_check + 2
            && j + k <= int(board->n_col()) - int(n_to_check) - 1)
        {
            if(board->get_status(board->n_col() - k, j + k)
                != Board::accessible)
                    {k++; continue;}
            for(unsigned m = 1; m <= n_to_check; m++)
            {
                if(board->get_status(board->n_col() - k - m, j + k + m)
                    != (who ? Board::white_stone : Board::black_stone))
                        goto next_loop6;
            }
            if(board->get_status(board->n_col() - k - n_to_check - 1,
                j + k + n_to_check + 1) == Board::accessible)
                    // A threat spotted
            {
                Threat threat;
                threat.threat_src = who;
                threat.pos1_x = board->n_col() - k - n_to_check;
                threat.pos1_y = j + k + n_to_check;
                threat.pos2_x = board->n_col() - k - 1;
                threat.pos2_y = j + k + 1;
                std::vector<unsigned> coord;
                coord.push_back(board->n_col() - k - n_to_check - 1);
                coord.push_back(j + k + n_to_check + 1);
                threat.key_pos_list.push_back(coord);
                coord[0] = board->n_col() - k; coord[1] = j + k;
                threat.key_pos_list.push_back(coord);
                result->push_back(threat);
            }
            next_loop6: k++;
        }
    }
    return *result;
}
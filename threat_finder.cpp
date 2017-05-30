#include "threat_finder.h"

// An implementation of KMP o(TヘTo)~~~  
std::vector<unsigned> find_occurances(
    const std::vector<Board::PosStatus> &v, unsigned arr[], unsigned len)
{
    std::vector<unsigned> *result = new std::vector<unsigned>;
    if(v.size() < len) return *result;
    int *funct = new int[v.size()];
    funct[0] = -1;
    for(int j = 1; j < int(v.size()); j++)
    {
        for(int i = funct[j - 1];; i = funct[i])
        {
            if(v[j] == v[i + 1])
            {
                funct[j] = i + 1;
                break;
            }
            else if(i == -1)
            {
                funct[j] = -1;
                break;
            }
        }
    }
    for(int i = 0, j = 0; i < int(v.size()); )
    {
        if(v[i] == arr[j]) {i++; j++;}
        else if(j == 0) i++;
        else j = funct[j - 1] + 1;
        if(j == int(len))
        {
            j = 0;
            result->push_back(i - len);
        }
    }
    delete[] funct;
    return *result;
}

std::vector<ThreatFinder::Threat> ThreatFinder::find_straight(
    bool who, unsigned n_to_check) const
{
    std::vector<Threat> *result = new std::vector<Threat>;
    unsigned *arr = new unsigned[n_to_check + 2];
    for(unsigned i = 0; i < n_to_check + 2; i++)
        arr[i] = (who ? Board::white_stone : Board::black_stone);
    arr[0] = Board::accessible;
    arr[n_to_check + 1] = Board::accessible;
    // Check the rows
    std::vector<Board::SelectedRow> rows = board->get_rows();
    for(std::vector<Board::SelectedRow>::const_iterator row = rows.begin();
        row != rows.end(); row++)
    {
        std::vector<unsigned> occurances
            = find_occurances(row->row_list, arr, n_to_check + 1);
        for(std::vector<unsigned>::iterator i = occurances.begin();
            i != occurances.end(); i++)
        {
            Threat threat;
            threat.threat_src = who;
            threat.pos1_x = row->begin_x + *i + 1;
            threat.pos1_y = row->begin_y;
            threat.pos2_x = row->begin_x + *i + n_to_check;
            threat.pos2_y = row->begin_y;
            std::vector<unsigned> coord;
            coord.push_back(row->begin_x + *i); coord.push_back(row->begin_y);
            threat.key_pos_list.push_back(coord);
            coord[0] = row->begin_x + *i + n_to_check - 1;
            threat.key_pos_list.push_back(coord);
            result->push_back(threat);
        }
    }
    delete[] arr;
    return *result;
}


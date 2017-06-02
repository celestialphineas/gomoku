#include "threat_finder.h"

// An implementation of KMP o(TヘTo)~~~  
std::vector<unsigned>* find_occurances(
    const std::vector<Board::PosStatus> &v, unsigned arr[], unsigned len)
{
    std::vector<unsigned> *result = new std::vector<unsigned>;
    if(v.size() < len) return result;
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
    return result;
}

std::vector<ThreatFinder::Threat>* ThreatFinder::find_straight(
    bool who, unsigned n_to_check) const
{
    std::vector<Threat> *result = new std::vector<Threat>;
    unsigned *arr = new unsigned[n_to_check + 2];
    for(unsigned i = 1; i < n_to_check + 1; i++)
        arr[i] = (who ? Board::white_stone : Board::black_stone);
    arr[0] = Board::accessible;
    arr[n_to_check + 1] = Board::accessible;

    // Check the rows
    std::vector<Board::SelectedRow>* rows = board->get_rows();
    for(std::vector<Board::SelectedRow>::const_iterator row = rows->begin();
        row != rows->end(); row++)
    {
        std::vector<unsigned>* occurances
            = find_occurances(row->row_list, arr, n_to_check + 2);
        for(std::vector<unsigned>::iterator i = occurances->begin();
            i != occurances->end(); i++)
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
            coord[0] = row->begin_x + *i + n_to_check + 1;
            threat.key_pos_list.push_back(coord);
            result->push_back(threat);
        }
        delete occurances;
    }
    delete rows; rows = NULL;

    // Check the cols
    std::vector<Board::SelectedRow>* cols = board->get_cols();
    for(std::vector<Board::SelectedRow>::const_iterator col = cols->begin();
        col != cols->end(); col++)
    {
        std::vector<unsigned>* occurances
            = find_occurances(col->row_list, arr, n_to_check + 2);
        for(std::vector<unsigned>::iterator i = occurances->begin();
            i != occurances->end(); i++)
        {
            Threat threat;
            threat.threat_src = who;
            threat.pos1_x = col->begin_x;
            threat.pos1_y = col->begin_y + *i + 1;
            threat.pos2_x = col->begin_x;
            threat.pos2_y = col->begin_y + *i + n_to_check;
            std::vector<unsigned> coord;
            coord.push_back(col->begin_x); coord.push_back(col->begin_y + *i);
            threat.key_pos_list.push_back(coord);
            coord[1] = col->begin_y + *i + n_to_check + 1;
            threat.key_pos_list.push_back(coord);
            result->push_back(threat);
        }
        delete occurances;
    }
    delete cols; cols = NULL;

    // Check the diags
    std::vector<Board::SelectedRow>* diags = board->get_diags();
    for(std::vector<Board::SelectedRow>::const_iterator diag = diags->begin();
        diag != diags->end(); diag++)
    {
        std::vector<unsigned>* occurances
            = find_occurances(diag->row_list, arr, n_to_check + 2);
        for(std::vector<unsigned>::iterator i = occurances->begin();
            i != occurances->end(); i++)
        {
            Threat threat;
            threat.threat_src = who;
            threat.pos1_x = diag->begin_x + *i + 1;
            threat.pos1_y = diag->begin_y + *i + 1;
            threat.pos2_x = diag->begin_x + *i + n_to_check;
            threat.pos2_y = diag->begin_y + *i + n_to_check;
            std::vector<unsigned> coord;
            coord.push_back(diag->begin_x + *i);
            coord.push_back(diag->begin_y + *i);
            threat.key_pos_list.push_back(coord);
            coord[0] = diag->begin_x + *i + n_to_check + 1;
            coord[1] = diag->begin_y + *i + n_to_check + 1;
            threat.key_pos_list.push_back(coord);
            result->push_back(threat);
        }
        delete occurances;
    }
    delete diags; diags = NULL;

    // Check the adiags
    std::vector<Board::SelectedRow>* adiags = board->get_adiags();
    for(std::vector<Board::SelectedRow>::const_iterator adiag = adiags->begin();
        adiag != adiags->end(); adiag++)
    {
        std::vector<unsigned>* occurances
            = find_occurances(adiag->row_list, arr, n_to_check + 2);
        for(std::vector<unsigned>::iterator i = occurances->begin();
            i != occurances->end(); i++)
        {
            Threat threat;
            threat.threat_src = who;
            threat.pos1_x = adiag->begin_x + *i + 1;
            threat.pos1_y = adiag->begin_y - *i - 1;
            threat.pos2_x = adiag->begin_x + *i + n_to_check;
            threat.pos2_y = adiag->begin_y - *i - n_to_check;
            std::vector<unsigned> coord;
            coord.push_back(adiag->begin_x + *i);
            coord.push_back(adiag->begin_y - *i);
            threat.key_pos_list.push_back(coord);
            coord[0] = adiag->begin_x + *i + n_to_check + 1;
            coord[1] = adiag->begin_y - *i - n_to_check - 1;
            threat.key_pos_list.push_back(coord);
            result->push_back(threat);
        }
        delete occurances;
    }
    delete adiags; adiags = NULL;

    delete[] arr;
    return result;
}

std::vector<ThreatFinder::Threat>* ThreatFinder::find_one_end_blocked(
    bool who, unsigned n_to_check) const
{
    std::vector<Threat> *result = new std::vector<Threat>;
    unsigned *arr1 = new unsigned[n_to_check + 2];
    for(unsigned i = 1; i < n_to_check + 1; i++)
        arr1[i] = (who ? Board::white_stone : Board::black_stone);
    arr1[0] = (who ? Board::black_stone : Board::white_stone);
    arr1[n_to_check + 1] = Board::accessible;
    unsigned *arr2 = new unsigned[n_to_check + 2];
    for(unsigned i = 1; i < n_to_check + 1; i++)
        arr2[i] = (who ? Board::white_stone : Board::black_stone);
    arr2[0] = Board::accessible;
    arr2[n_to_check + 1] = (who ? Board::black_stone : Board::white_stone);

    // Check the rows
    std::vector<Board::SelectedRow>* rows = board->get_rows();
    for(std::vector<Board::SelectedRow>::const_iterator row = rows->begin();
        row != rows->end(); row++)
    {
        if(row->row_list.size() < n_to_check + 1) continue;
        std::vector<unsigned>* occurances
            = find_occurances(row->row_list, arr1, n_to_check + 2);
        for(std::vector<unsigned>::iterator i = occurances->begin();
            i != occurances->end(); i++)
        {
            Threat threat;
            threat.threat_src = who;
            threat.pos1_x = row->begin_x + *i + 1;
            threat.pos1_y = row->begin_y;
            threat.pos2_x = row->begin_x + *i + n_to_check;
            threat.pos2_y = row->begin_y;
            std::vector<unsigned> coord;
            coord.push_back(row->begin_x + *i + n_to_check + 1);
            coord.push_back(row->begin_y);
            threat.key_pos_list.push_back(coord);
            result->push_back(threat);
        }
        delete occurances;
        occurances = find_occurances(row->row_list, arr2, n_to_check + 2);
        for(std::vector<unsigned>::iterator i = occurances->begin();
            i != occurances->end(); i++)
        {
            Threat threat;
            threat.threat_src = who;
            threat.pos1_x = row->begin_x + *i + 1;
            threat.pos1_y = row->begin_y;
            threat.pos2_x = row->begin_x + *i + n_to_check;
            threat.pos2_y = row->begin_y;
            std::vector<unsigned> coord;
            coord.push_back(row->begin_x + *i);
            coord.push_back(row->begin_y);
            threat.key_pos_list.push_back(coord);
            result->push_back(threat);
        }
        bool blocked_by_edge = true;
        for(unsigned i = 0; i < n_to_check; i++)
        {
            if(row->row_list[i] !=
                (who ? Board::white_stone : Board::black_stone))
                    {blocked_by_edge = false; break;}
        }
        if(blocked_by_edge && row->row_list[n_to_check] == Board::accessible)
        {
            Threat threat;
            threat.threat_src = who;
            threat.pos1_x = 1; threat.pos1_y = row->begin_y;
            threat.pos2_x = n_to_check; threat.pos2_y = row->begin_y;
            std::vector<unsigned> coord;
            coord.push_back(n_to_check + 1);
            coord.push_back(row->begin_y);
            threat.key_pos_list.push_back(coord);
            result->push_back(threat);
        }
        blocked_by_edge = true;
        for(unsigned i = row->row_list.size() - n_to_check;
            i < row->row_list.size(); i++)
        {
            if(row->row_list[i] != 
                (who ? Board::white_stone : Board::black_stone))
                    {blocked_by_edge = false; break;}
        }
        if(blocked_by_edge
        && row->row_list[row->row_list.size() - n_to_check - 1] == Board::accessible)
        {
            Threat threat;
            threat.threat_src = who;
            threat.pos1_x = row->begin_x + row->row_list.size() - n_to_check;
            threat.pos1_y = row->begin_y;
            threat.pos2_x = row->begin_x + row->row_list.size() - 1;
            threat.pos2_y = row->begin_y;
            std::vector<unsigned> coord;
            coord.push_back(row->begin_x + row->row_list.size() - n_to_check - 1);
            coord.push_back(row->begin_y);
            threat.key_pos_list.push_back(coord);
            result->push_back(threat);
        }
        delete occurances;
    }
    delete rows; rows = NULL;

    // Check the cols
    std::vector<Board::SelectedRow>* cols = board->get_cols();
    for(std::vector<Board::SelectedRow>::const_iterator col = cols->begin();
        col != cols->end(); col++)
    {
        if(col->row_list.size() < n_to_check + 1) continue;
        std::vector<unsigned>* occurances
            = find_occurances(col->row_list, arr1, n_to_check + 2);
        for(std::vector<unsigned>::iterator i = occurances->begin();
            i != occurances->end(); i++)
        {
            Threat threat;
            threat.threat_src = who;
            threat.pos1_x = col->begin_x;
            threat.pos1_y = col->begin_y + *i + 1;
            threat.pos2_x = col->begin_x;
            threat.pos2_y = col->begin_y + *i + n_to_check;
            std::vector<unsigned> coord;
            coord.push_back(col->begin_x);
            coord.push_back(col->begin_y + *i + n_to_check + 1);
            threat.key_pos_list.push_back(coord);
            result->push_back(threat);
        }
        delete occurances;
        occurances = find_occurances(col->row_list, arr2, n_to_check + 2);
        for(std::vector<unsigned>::iterator i = occurances->begin();
            i != occurances->end(); i++)
        {
            Threat threat;
            threat.threat_src = who;
            threat.pos1_x = col->begin_x;
            threat.pos1_y = col->begin_y + *i + 1;
            threat.pos2_x = col->begin_x;
            threat.pos2_y = col->begin_y + *i + n_to_check;
            std::vector<unsigned> coord;
            coord.push_back(col->begin_x);
            coord.push_back(col->begin_y + *i);
            threat.key_pos_list.push_back(coord);
            result->push_back(threat);
        }
        bool blocked_by_edge = true;
        for(unsigned i = 0; i < n_to_check; i++)
        {
            if(col->row_list[i] !=
                (who ? Board::white_stone : Board::black_stone))
                    {blocked_by_edge = false; break;}
        }
        if(blocked_by_edge && col->row_list[n_to_check] == Board::accessible)
        {
            Threat threat;
            threat.threat_src = who;
            threat.pos1_x = col->begin_x; threat.pos1_y = 1;
            threat.pos2_x = col->begin_x; threat.pos2_y = n_to_check;
            std::vector<unsigned> coord;
            coord.push_back(col->begin_x);
            coord.push_back(n_to_check + 1);
            threat.key_pos_list.push_back(coord);
            result->push_back(threat);
        }
        blocked_by_edge = true;
        for(unsigned i = col->row_list.size() - n_to_check;
            i < col->row_list.size(); i++)
        {
            if(col->row_list[i] !=
                (who ? Board::white_stone : Board::black_stone))
                    {blocked_by_edge = false; break;}
        }
        if(blocked_by_edge
        && col->row_list[col->row_list.size() - n_to_check - 1] == Board::accessible)
        {
            Threat threat;
            threat.threat_src = who;
            threat.pos1_x = col->begin_x;
            threat.pos1_y = col->begin_y + col->row_list.size() - n_to_check;
            threat.pos2_x = col->begin_x;
            threat.pos2_y = col->begin_y + col->row_list.size() - 1;
            std::vector<unsigned> coord;
            coord.push_back(col->begin_x);
            coord.push_back(col->begin_y + col->row_list.size() - n_to_check - 1);
            threat.key_pos_list.push_back(coord);
            result->push_back(threat);
        }
        delete occurances;
    }
    delete cols; cols = NULL;

    // Check the diags
    std::vector<Board::SelectedRow>* diags = board->get_diags();
    for(std::vector<Board::SelectedRow>::const_iterator diag = diags->begin();
        diag != diags->end(); diag++)
    {
        if(diag->row_list.size() < n_to_check + 1) continue;
        std::vector<unsigned>* occurances
            = find_occurances(diag->row_list, arr1, n_to_check + 2);
        for(std::vector<unsigned>::iterator i = occurances->begin();
            i != occurances->end(); i++)
        {
            Threat threat;
            threat.threat_src = who;
            threat.pos1_x = diag->begin_x + *i + 1;
            threat.pos1_y = diag->begin_y + *i + 1;
            threat.pos2_x = diag->begin_x + *i + n_to_check;
            threat.pos2_y = diag->begin_y + *i + n_to_check;
            std::vector<unsigned> coord;
            coord.push_back(diag->begin_x + *i + n_to_check + 1);
            coord.push_back(diag->begin_y + *i + n_to_check + 1);
            threat.key_pos_list.push_back(coord);
            result->push_back(threat);
        }
        delete occurances;
        occurances = find_occurances(diag->row_list, arr2, n_to_check + 2);
        for(std::vector<unsigned>::iterator i = occurances->begin();
            i != occurances->end(); i++)
        {
            Threat threat;
            threat.threat_src = who;
            threat.pos1_x = diag->begin_x + *i + 1;
            threat.pos1_y = diag->begin_y + *i + 1;
            threat.pos2_x = diag->begin_x + *i + n_to_check;
            threat.pos2_y = diag->begin_y + *i + n_to_check;
            std::vector<unsigned> coord;
            coord.push_back(diag->begin_x + *i);
            coord.push_back(diag->begin_y + *i);
            threat.key_pos_list.push_back(coord);
            result->push_back(threat);
        }
        bool blocked_by_edge = true;
        for(unsigned i = 0; i < n_to_check; i++)
        {
            if(diag->row_list[i] !=
                (who ? Board::white_stone : Board::black_stone))
                    {blocked_by_edge = false; break;}
        }
        if(blocked_by_edge && diag->row_list[n_to_check] == Board::accessible)
        {
            Threat threat;
            threat.threat_src = who;
            threat.pos1_x = diag->begin_x; threat.pos1_y = diag->begin_y;
            threat.pos2_x = diag->begin_x + n_to_check - 1;
            threat.pos2_y = diag->begin_y + n_to_check - 1;
            std::vector<unsigned> coord;
            coord.push_back(diag->begin_x + n_to_check);
            coord.push_back(diag->begin_y + n_to_check);
            threat.key_pos_list.push_back(coord);
            result->push_back(threat);
        }
        blocked_by_edge = true;
        for(unsigned i = diag->row_list.size() - n_to_check;
            i < diag->row_list.size(); i++)
        {
            if(diag->row_list[i] !=
                (who ? Board::white_stone : Board::black_stone))
                    {blocked_by_edge = false; break;}
        }
        if(blocked_by_edge
        && diag->row_list[diag->row_list.size() - n_to_check - 1] == Board::accessible)
        {
            Threat threat;
            threat.threat_src = who;
            threat.pos1_x = diag->begin_x + diag->row_list.size() - n_to_check;
            threat.pos1_y = diag->begin_y + diag->row_list.size() - n_to_check;
            threat.pos2_x = diag->begin_x + diag->row_list.size() - 1;
            threat.pos2_y = diag->begin_y + diag->row_list.size() - 1;
            std::vector<unsigned> coord;
            coord.push_back(diag->begin_x + diag->row_list.size() - n_to_check - 1);
            coord.push_back(diag->begin_y + diag->row_list.size() - n_to_check - 1);
            threat.key_pos_list.push_back(coord);
            result->push_back(threat);
        }
        delete occurances;
    }
    delete diags; diags = NULL;

    // Check the adiags
    std::vector<Board::SelectedRow>* adiags = board->get_adiags();
    for(std::vector<Board::SelectedRow>::const_iterator adiag = adiags->begin();
        adiag != adiags->end(); adiag++)
    {
        if(adiag->row_list.size() < n_to_check + 1) continue;
        std::vector<unsigned>* occurances
            = find_occurances(adiag->row_list, arr1, n_to_check + 2);
        for(std::vector<unsigned>::iterator i = occurances->begin();
            i != occurances->end(); i++)
        {
            Threat threat;
            threat.threat_src = who;
            threat.pos1_x = adiag->begin_x + *i + 1;
            threat.pos1_y = adiag->begin_y - *i - 1;
            threat.pos2_x = adiag->begin_x + *i + n_to_check;
            threat.pos2_y = adiag->begin_y - *i - n_to_check;
            std::vector<unsigned> coord;
            coord.push_back(adiag->begin_x + *i + n_to_check + 1);
            coord.push_back(adiag->begin_y - *i - n_to_check - 1);
            threat.key_pos_list.push_back(coord);
            result->push_back(threat);
        }
        delete occurances;
        occurances = find_occurances(adiag->row_list, arr2, n_to_check + 2);
        for(std::vector<unsigned>::iterator i = occurances->begin();
            i != occurances->end(); i++)
        {
            Threat threat;
            threat.threat_src = who;
            threat.pos1_x = adiag->begin_x + *i + 1;
            threat.pos1_y = adiag->begin_y - *i - 1;
            threat.pos2_x = adiag->begin_x + *i + n_to_check;
            threat.pos2_y = adiag->begin_y - *i - n_to_check;
            std::vector<unsigned> coord;
            coord.push_back(adiag->begin_x + *i);
            coord.push_back(adiag->begin_y - *i);
            threat.key_pos_list.push_back(coord);
            result->push_back(threat);
        }
        bool blocked_by_edge = true;
        for(unsigned i = 0; i < n_to_check; i++)
        {
            if(adiag->row_list[i] !=
                (who ? Board::white_stone : Board::black_stone))
                    {blocked_by_edge = false; break;}
        }
        if(blocked_by_edge && adiag->row_list[n_to_check] == Board::accessible)
        {
            Threat threat;
            threat.threat_src = who;
            threat.pos1_x = adiag->begin_x; threat.pos1_y = adiag->begin_y;
            threat.pos2_x = adiag->begin_x + n_to_check - 1;
            threat.pos2_y = adiag->begin_y - n_to_check + 1;
            std::vector<unsigned> coord;
            coord.push_back(adiag->begin_x + n_to_check);
            coord.push_back(adiag->begin_y - n_to_check);
            threat.key_pos_list.push_back(coord);
            result->push_back(threat);
        }
        blocked_by_edge = true;
        for(unsigned i = adiag->row_list.size() - n_to_check;
            i < adiag->row_list.size(); i++)
        {
            if(adiag->row_list[i] !=
                (who ? Board::white_stone : Board::black_stone))
                    {blocked_by_edge = false; break;}
        }
        if(blocked_by_edge
        && adiag->row_list[adiag->row_list.size() - n_to_check - 1] == Board::accessible)
        {
            Threat threat;
            threat.threat_src = who;
            threat.pos1_x = adiag->begin_x + adiag->row_list.size() - n_to_check;
            threat.pos1_y = adiag->begin_y - adiag->row_list.size() + n_to_check;
            threat.pos2_x = adiag->begin_x + adiag->row_list.size() - 1;
            threat.pos2_y = adiag->begin_y - adiag->row_list.size() + 1;
            std::vector<unsigned> coord;
            coord.push_back(adiag->begin_x + adiag->row_list.size() - n_to_check - 1);
            coord.push_back(adiag->begin_y - adiag->row_list.size() + n_to_check + 1);
            threat.key_pos_list.push_back(coord);
            result->push_back(threat);
        }
        delete occurances;
    }
    delete adiags; adiags = NULL;
    delete[] arr1; delete[] arr2;
    return result;
}
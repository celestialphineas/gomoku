#include "threat_finder.h"

// std::vector<ThreatFinder::Threat> ThreatFinder::find_straight(
//     bool who, unsigned n_to_check) const
// {
//     // Check the rows
//     std::vector<Board::SelectedRow> rows = board->get_rows();
//     for(std::vector<Board::SelectedRow>::const_iterator row = rows.begin();
//         row != rows.end(); row++)
//     {

//     }
// }

// An implementation of KMP o(TヘTo)~~~  
std::vector<unsigned> find_occurance(
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
    delete funct;
    return *result;
}

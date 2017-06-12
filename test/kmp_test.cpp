#include "board.h"
#include "threat_finder.h"

std::vector<unsigned> find_occurance(
    const std::vector<Board::PosStatus> &v, unsigned arr[], unsigned len);

int main(void)
{
    for(;;)
    {
        std::vector<unsigned> target;
        unsigned arr[100];
        for(;;)
        {
            int hello;
            std::cin >> hello;
            if(hello < 0) break;
            target.push_back(unsigned(hello));
        }
        unsigned i = 0;
        for(;;)
        {
            int hello;
            std::cin >> hello;
            if(hello < 0) break;
            arr[i++] = unsigned(hello);
        }
        std::vector<unsigned> occurances = 
            find_occurance(target, arr, i);
        for(std::vector<unsigned>::iterator j = occurances.begin();
            j != occurances.end(); j++)
        {
            std::cout << *j << ' ';
        }
        std::cout << std::endl;
    }    
}
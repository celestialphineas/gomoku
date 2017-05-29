#include <iostream>
#include "board.h"
#include "std_gomoku_judge.h"
#include "threat_finder.h"

void print_board(const Board& board)
{
    for(unsigned i = 1; i <= board.n_col(); i++)
        std::cout << i%10 << " ";
    std::cout << std::endl << std::endl;
    for(unsigned j = 1; j <= board.n_row(); j++)
    {
        for(unsigned i = 1; i <= board.n_col(); i++)
        {
            std::cout << (unsigned)board.get_status(i, j) << " ";
        }
        std::cout << "  " << j << std::endl;
    }
    return;
}

void print_threats(const std::vector<Threat> &src)
{
    if(src.empty()) puts("No threats is found.");
    else
    {
        for(std::vector<Threat>::const_iterator i = src.begin();
            i != src.end(); i++)
        {
            std::cout << "Threat from "
                << (i->threat_src ? "white" : "black") << ":" << std::endl;
            std::cout << i->pos1_x << " " << i->pos1_y << " "
                << i->pos2_x << " " << i->pos2_y << std::endl;
            std::cout << "Key positions: ";
            for(std::vector<std::vector<unsigned> >::const_iterator
                j = i->key_pos_list.begin(); j != i->key_pos_list.end(); j++)
            {
                std::cout << (*j)[0] << " " << (*j)[1] << "  ";
            }
            std::cout << std::endl;
        }
    }
    return;
}

int main(void)
{
    Board *board = new Board;
    WinningJudge *judge = new StandardGomokuJudge(board);

    while(1)
    {
        system("cls");
        print_board(*board);
        ThreatFinder threat_finder(board);
        std::vector<Threat> black_threats
            = threat_finder.find_straight(ThreatFinder::black, 3);
        std::vector<Threat> white_threats
            = threat_finder.find_straight(ThreatFinder::white, 3);
        print_threats(black_threats); print_threats(white_threats);
        std::cout << "Operation sequence: ";
        std::deque<Te> sequence = board->get_game_sequence();
        for(std::deque<Te>::iterator i = sequence.begin();
            i != sequence.end(); i++)
        {
            printf("(%u %s %s : %u %u) ",
                i->id(),
                i->is_black() ? "black" : "white",
                i->is_te() ? "te" : "remove",
                i->x(), i->y());
        } std::cout << std::endl;
        std::cout << "Game status: ";
        switch(judge->judge())
        {
            case WinningJudge::black_wins:
                std::cout << "black wins" << std::endl;
                printf("(%u, %u) -> (%u, %u)\n",
                    judge->get_marker1_x(), judge->get_marker1_y(),
                    judge->get_marker2_x(), judge->get_marker2_y());
                break;
            case WinningJudge::white_wins:
                std::cout << "white wins" << std::endl; break;
                printf("(%u, %u) -> (%u, %u)\n",
                    judge->get_marker1_x(), judge->get_marker1_y(),
                    judge->get_marker2_x(), judge->get_marker2_y());
                break;
            default:
                std::cout << "ongoing" << std::endl << std::endl;
                break;
        }
        char instruction;
        std::cin >> instruction;
        int x, y;
        switch(instruction)
        {
            case 'b':
                std::cin >> x >> y;
                board->black_te(x, y); break;
            case 'w':
                std::cin >> x >> y;
                board->white_te(x, y); break;
            case 'n':
                std::cin >> x >> y;
                board->black_remove(x, y); break;
            case 'e':
                std::cin >> x >> y;
                board->white_remove(x, y); break;
            case 'u':
                board->undo(); break;
            case 'c':
                std::cin >> x >> y;
                delete board; board = new Board(x, y);
                delete judge; judge = new StandardGomokuJudge(board);
                break;
            case 'q':
                return 0;
            default: break;
        }
    }
    return 0;
}


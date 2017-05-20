#include <iostream>
#include "board.h"
#include "winning_judge.h"

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

int main(void)
{
    Board *board = new Board;
    WinningJudge *judge = new FreeStyleJudge(board);

    while(1)
    {
        system("cls");
        print_board(*board);
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
                delete judge; judge = new FreeStyleJudge(board);
                break;
            case 'q':
                return 0;
            default: break;
        }
    }
    return 0;
}


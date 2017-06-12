#include "board.h"
#include "std_gomoku_judge.h"
#include "free_style_judge.h"
#include "primary_ai.h"
#include <iostream>

void print_board(const Board& board)
{
    for(unsigned i = 1; i <= board.n_col(); i++)
        std::cout << i%10 << " ";
    std::cout << std::endl << std::endl;
    for(unsigned j = 1; j <= board.n_row(); j++)
    {
        for(unsigned i = 1; i <= board.n_col(); i++)
        {
            if(board.get_status(i, j) == Board::white_stone)
                std::cout << "o ";
            else if(board.get_status(i, j) == Board::black_stone)
                std::cout << "* ";
            else std::cout << "  ";
        }
        std::cout << "  " << j << std::endl;
    }
    return;
}

int main(void)
{
    Board board;
    FreeStyleJudge judge(&board);
    system("cls");
    print_board(board);
    for(;;)
    {
        PrimaryAI black_player(&board, Player::black, &judge);
        PrimaryAI white_player(&board, Player::white, &judge);
        black_player.te();
        system("cls");
        print_board(board);
        if(judge.judge() == WinningJudge::black_wins)
        {
            std::cout << "Black wins!" << std::endl;
            return 0;
        }
        // system("pause");
        white_player.te();
        system("cls");
        print_board(board);
        if(judge.judge() == WinningJudge::white_wins)
        {
            std::cout << "White wins!" << std::endl;
            return 0;
        }
        // system("pause");
    }
}
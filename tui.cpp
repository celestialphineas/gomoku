#include "game_factory.h"
#include <iostream>

bool TUI_game_settings(
    unsigned &n_rounds,
    GameFactory::PlayerType &player1,
    GameFactory::PlayerType &player2,
    GameFactory::GameRule &game_rule,
    GameFactory::GameJudge &game_judge,
    unsigned &board_dim_width,
    unsigned &board_dim_height);

void print_game(Game *game);
bool TUI_test_choice(Game *game);

int main(void)
{
    GameFactory game_factory;
    for(;;)
    {
        unsigned n_rounds = 1;
        GameFactory::PlayerType player1;
        GameFactory::PlayerType player2;
        GameFactory::GameRule game_rule;
        GameFactory::GameJudge game_judge;
        unsigned board_dim_height, board_dim_width;
        player1 = GameFactory::human_player;
        player2 = GameFactory::primary_ai;
        game_rule = GameFactory::standard_rule;
        game_judge = GameFactory::standard_gomoku;
        board_dim_width = 15;
        board_dim_height = 15;
        if(!TUI_game_settings(n_rounds, player1, player2, game_rule, game_judge,
            board_dim_width, board_dim_height))
                return 0;
        Game *new_game = game_factory.create_game(
            n_rounds, player1, player2, game_rule, game_judge, board_dim_width,
            board_dim_height);
        if(!new_game) continue;
            // Start the game
        for(;;)
        {
            print_game(new_game);
            if(!TUI_test_choice(new_game)) break;
        }
    }
    return 0;
}

bool TUI_game_settings(
    unsigned &n_rounds,
    GameFactory::PlayerType &player1,
    GameFactory::PlayerType &player2,
    GameFactory::GameRule &game_rule,
    GameFactory::GameJudge &game_judge,
    unsigned &board_dim_width,
    unsigned &board_dim_height)
{
    unsigned choice;
    settings:
    system("cls");
    printf("\
Game Settings\n\
1. Set the number of rounds\n\
2. Set Player 1\n\
3. Set Player 2\n\
4. Set game rule\n\
5. Set winning judge\n\
6. Set the board dimension\n\
7. Start game!\n\
8. Exit\n\
> ");
    std::cin >> choice;
    system("cls");
    switch(choice)
    {
        case 1:
            printf("Please insert an integer:\n> ");
            std::cin >> n_rounds;
            goto settings;
        case 2:
            printf("Player 1 settings\n");
            printf("1. Human player\n2. AI\n> ");
            std::cin >> choice;
            switch(choice)
            {
                case 1:
                    player1 = GameFactory::human_player;
                    goto settings;
                case 2:
                    player1 = GameFactory::primary_ai;
                    goto settings;
                default:
                    goto settings;
            }
        case 3:
            printf("Player 2 settings\n");
            printf("1. Human player\n2. AI\n> ");
            std::cin >> choice;
            switch(choice)
            {
                case 1:
                    player2 = GameFactory::human_player;
                    goto settings;
                case 2:
                    player2 = GameFactory::primary_ai;
                    goto settings;
                default:
                    goto settings;
            }
        case 4:
            goto settings;
        case 5:
            printf("Winning judge settings\n");
            printf("1. Free-style gomoku\n2. Standard gomoku\n> ");
            std::cin >> choice;
            switch(choice)
            {
                case 1:
                    game_judge = GameFactory::free_style_gomoku;
                    goto settings;
                case 2:
                    game_judge = GameFactory::standard_gomoku;
                    goto settings;
                default:
                    goto settings;
            }
        case 6:
            printf("Set the width:\n> ");
            std::cin >> board_dim_width;
            printf("Set the height:\n> ");
            std::cin >> board_dim_height;
            goto settings;
        case 7:
            return true;
        case 8:
            return false;
        default:
            goto settings;
    }
    return true;
}

void print_game(Game *game)
{
    system("cls");
    printf("Round %u/%u\t\t", game->current_round(), game->n_rounds());
    printf("Board width: %u\t\t", game->board_width());
    printf("Board height: %u\n", game->board_height());
    printf("Next round: %s\t\t",
        game->next_round_validity() ? "available" : "invalid");
    printf("Previous round: %s\n",
        game->previous_round_validity() ? "available" : "invalid");
    printf("Current winning: ");
    switch(game->current_status())
    {
        case Game::ongoing : printf("ongoing"); break;
        case Game::black_wins : printf("black wins"); break;
        case Game::white_wins : printf("white wins"); break;
        case Game::not_started : printf("not started"); break;
        default: printf("ERROR!"); break;
    }
    printf("\t");
    printf("Current input status: %s\n", 
        game->input_allowed() ? "allowed" : "forbidden");
    
    for(unsigned i = 1; i <= game->board_width(); i++)
        printf(" %u ", i%10);
    printf("\n");
    for(unsigned j = 1; j <= game->board_height(); j++)
    {
        for(unsigned i = 1; i <= game->board_width(); i++)
        {
            switch(game->pos_status(i, j))
            {
                case Game::accessible:
                    printf(" + "); break;
                case Game::black_stone:
                    printf(" x "); break;
                case Game::white_stone:
                    printf(" o "); break;
                default:
                    printf("   "); break;
            }
        }
        printf("  %u\n", j);
    }
    
    return;
}

bool TUI_test_choice(Game *game)
{
    unsigned choice;
    unsigned x, y;
    rechoose:
    printf("\nPlease choose one option to continue:\n");
    printf("1. Go next step\n");
    printf("2. Input a te\n");
    printf("3. Switch to next round\n");
    printf("4. Switch to previous round\n");
    printf("5. Exit the game\n");
    printf("> ");
    std::cin >> choice;
    switch(choice)
    {
        case 1:
            game->next();
            break;
        case 2:
            printf("x> ");
            std::cin >> x;
            printf("y> ");
            std::cin >> y;
            game->input(x, y);
            break;
        case 3:
            game->switch_to_next_round();
            break;
        case 4:
            game->switch_to_previous_round();
            break;
        case 5:
            return false;
        default: goto rechoose;
    }
    return true;
}
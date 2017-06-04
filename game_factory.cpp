#include "game_factory.h"

Game* GameFactory::create_game(
    unsigned n_rounds,
    GameFactory::PlayerType player1,
    GameFactory::PlayerType player2,
    GameFactory::GameRule game_rule,
    GameFactory::GameJudge game_judge,
    unsigned width,
    unsigned height)
{
    // Handle invalid inputs
    if(n_rounds == 0 || n_rounds > max_round_threshold)
        return NULL; 
    if(width < min_board_dim_width_threshold) return NULL;
    if(height < min_board_dim_height_threshold) return NULL;
    if(width > max_baord_dim_width_threshold) return NULL;
    if(height > max_board_dim_height_threshold) return NULL;

    Game *new_game = new Game;
    new_game->input_locked = true;
    new_game->current = 0;
    new_game->rounds = n_rounds;
    new_game->game_statuses = new Game::GameStatus[n_rounds];
    new_game->white_players = new Player*[n_rounds];
    new_game->black_players = new Player*[n_rounds];
    new_game->judges = new WinningJudge*[n_rounds];
    new_game->boards = new Boards*[n_rounds];
    new_game->organizers = new GameOrganizer*[n_rounds];

    for(unsigned i = 0; i < n_rounds; i++)
    {
        new_game->game_statuses[i] = Game::not_started;
        new_game->boards[i] = new Board(height, width);
        switch(game_judge)
        {
            case free_style_gomoku:
                new_game->judges[i]
                    = new FreeStyleJudge(new_game->boards[i]);
                break;
            case standard_gomoku:
                new_game->judges[i]
                    = new StandardGomokuJudge(new_game->boards[i]);
                break;
            default:
                new_game->judges[i]
                    = new StandardGomokuJudge(new_game->boards[i]);
                break;
        }
        switch(player1)
        {
            case human_player:
                new_game->black_players[i]
                    = new HumanPlayer(new_game->boards[i], Player::black);
                break;
            case primary_ai:
                new_game->black_players[i]
                    = new PrimaryAI(new_game->boards[i],
                        Player::black, new_game->judges[i]);
                break;
            default:
                new_game->black_players[i]
                    = new PrimaryAI(new_game->boards[i],
                        Player::black, new_game->judges[i]);
                break;
        }
        switch(player2)
        {
            case human_player:
                new_game->white_players[i]
                    = new HumanPlayer(new_game->boards[i], Player::white);
                break;
            case primary_ai:
                new_game->white_players[i]
                    = new PrimaryAI(new_game->boards[i],
                        Player::white, new_game->judges[i]);
                break;
            default:
                new_game->white_players[i]
                    = new PrimaryAI(new_game->boards[i],
                        Player::white, new_game->judges[i]);
                break;
        }
        switch(GameRule)
        {
            case standard_rule:
                new_game->organizers[i]
                    = new StdOrganizer(new_game->boards[i], new_game->judges[i],
                        new_game->black_players[i], new_game->white_players[i]);
                break;                    
            default:
                new_game->organizers[i]
                    = new StdOrganizer(new_game->boards[i], new_game->judges[i],
                        new_game->black_players[i], new_game->white_players[i]);
                break;                    
        }
    }

    // Exchange the players for some games
    for(unsigned j = 1; j < n_rounds; j += 2)
    {
        new_game->current = j;
        new_game->exchange_player();
        new_game->current = 0;
    }

    return new_game;
}
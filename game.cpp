#include "game.h"

Game::Game(const Game& src)
{
    input_status = src.input_status;
    current_round_index = src.current_round_index;
    rounds = src.rounds;
    game_statuses = new GameStatus[rounds];
    white_players = new Player*[rounds];
    black_players = new Player*[rounds];
    judges = new WinningJudge*[rounds];
    boards = new Boards*[rounds];
    organizers = new GameOrganizer*[rounds];
    for(unsigned i = 0; i < rounds; i++)
    {
        game_statuses[i] = src.game_statuses[i];
        boards[i] = new Board(*(src.boards[i]));
        judges[i] = src.judges[i]->clone();
        judges[i]->set_board(boards[i]);
        black_players[i] = src.black_players[i]->clone();
        white_players[i] = src.white_players[i]->clone();
        black_players[i]->set_board(boards[i]);
        white_players[i]->set_board(boards[i]);
        if(black_players[i]->player_type == Player::human_player)
            dynamic_cast<AIPlayer*>(black_player[i])->set_judge(judges[i]);
        if(white_players[i]->player_type == Player::ai_player)
            dynamic_cast<AIPlayer*>(white_player[i])->set_judge(judges[i]);
        organizers[i] = src.organizers[i]->clone();
        organizers[i]->set_board(boards[i]);
        organizers[i]->set_judge(judges[i]);
        organizers[i]->set_black(black_players[i]);
        organizers[i]->set_white(white_players[i]);
    }
    return;
}

Game::~Game()
{
    for(unsigned i = 0; i < rounds; i++)
    {
        delete organizers[i]; delete black_players[i];
        delete white_players[i]; delete judges[i];
        delete boards[i];
    }
    delete[] game_statuses; delete[] boards;
    delete[] judges; delete[] black_players;
    delete[] white_players; delete[] organizers;
}

bool Game::switch_to_round(unsigned round_index)
{
    if(round_index <= 0 || round_index > rounds) return false;
    current_round_index = round_index - 1;
    return true;
}

bool Game::next_round_validity() const
{
    if(current_round_index >= rounds) return false; 
    unsigned n_black_wins = 0, n_white_wins = 0;
    for(unsigned i = 0; i < current_round_index; i++)
    {
        if(game_statuses[i] == black_wins) n_black_wins++;
        else if(game_statuses[i] == white_wins) n_white_wins++;
    }
    if(n_black_wins > (rounds + 1)/2 || n_white_wins > (rounds + 1)/2)
        return false;
    return true;
}

bool Game::previous_round_validity() const
{
    if(current_round_index <= 1) return false;
    return true;
}

bool Game::switch_to_next_round()
{
    if(next_round_validity()) {current_round_index++; return true;}
    else return false;
}

bool Game::switch_to_previous_round()
{
    if(previous_round_validity()) {current_round_index--; return true;}
    else return false;
}

void Game::exchange_player()
{
    Player *temp = black_players[current_round_index];
    black_players[current_round_index] = white_players[current_round_index];
    white_players[current_round_index] = temp;
    game_organizer[current_round_index]->exchange_player();
}
#include "game.h"

Game::Game(const Game& src)
{
    input_locked = src.input_locked;
    current = src.current;
    rounds = src.rounds;
    game_statuses = new GameStatus[rounds];
    white_players = new Player*[rounds];
    black_players = new Player*[rounds];
    judges = new WinningJudge*[rounds];
    boards = new Board*[rounds];
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
        if(black_players[i]->player_type() == Player::human_player)
            dynamic_cast<AIPlayer*>(black_players[i])->set_judge(judges[i]);
        if(white_players[i]->player_type() == Player::ai_player)
            dynamic_cast<AIPlayer*>(white_players[i])->set_judge(judges[i]);
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
    current = round_index - 1;
    return true;
}

bool Game::next_round_validity() const
{
    if(current >= rounds) return false; 
    unsigned n_black_wins = 0, n_white_wins = 0;
    for(unsigned i = 0; i < current; i++)
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
    if(current <= 1) return false;
    return true;
}

bool Game::switch_to_next_round()
{
    if(next_round_validity()) {current++; return true;}
    else return false;
}

bool Game::switch_to_previous_round()
{
    if(previous_round_validity()) {current--; return true;}
    else return false;
}

void Game::exchange_player()
{
    Player *temp = black_players[current];
    black_players[current] = white_players[current];
    white_players[current] = temp;
    organizers[current]->exchange_player();
    return;
}

void Game::next()
{
    // Start a game
    if(game_statuses[current] == not_started)
    {
        game_statuses[current] = ongoing;
        GameOrganizer::CurrentRequest request = organizers[current]->current_request();
        input_locked = true;
        if((request == GameOrganizer::black_te
            || request == GameOrganizer::black_remove
            || request == GameOrganizer::black_exchange)
            && black_players[current]->player_type() == Player::human_player)
                input_locked = false;
        if((request == GameOrganizer::white_te
            || request == GameOrganizer::white_remove
            || request == GameOrganizer::white_exchange)
            && white_players[current]->player_type() == Player::human_player)
                input_locked = false;
        game_statuses[current] = judges[current]->judge();
        if(game_statuses[current] != ongoing) input_locked = true;
        return;
    }
    // If a game has already ended, do nothing except blocking the input
    if(game_statuses[current] != ongoing)
        {input_locked = true; return;}
    
    // If the input is not locked, simply refuse to go to the next step
    if(!input_locked) return;

    // For the locked input status, push the game precedure forward
    GameOrganizer::CurrentRequest request
        = organizers[current]->current_request();
    switch(request)
    {
        case GameOrganizer::black_te :
            black_players[current]->te();
            break;
        case GameOrganizer::black_remove :
            black_players[current]->remove();
            break;
        case GameOrganizer::black_exchange :
            if(black_players[current]->exchange_choice())
                exchange_player();
            break;
        case GameOrganizer::white_te :
            white_players[current]->te();
            break;
        case GameOrganizer::white_remove :
            white_players[current]->remove();
            break;
        case GameOrganizer::white_exchange :
            if(white_players[current]->exchange_choice())
                exchange_player();
            break;
        default: break;
    }

    // End the game if the judge meets a win-loss
    if(judges[current]->judge() != ongoing)
    {
        organizers[current]->next();
        game_statuses[current] = judges[current]->judge();
        input_locked = true;
        return;
    }

    // If the new concerned player is a human, unlock the input
    organizers[current]->next();
    GameOrganizer::CurrentRequest new_request
        = organizers[current]->current_request();
    if((new_request == GameOrganizer::black_te
        || new_request == GameOrganizer::black_remove
        || new_request == GameOrganizer::black_exchange)
        && black_players[current]->player_type() == human_player)

    {
        input_locked = false;
        return;
    }
    else if((new_request == GameOrganizer::white_te
        || new_request == GameOrganizer::white_remove
        || new_request == GameOrganizer::white_exchange)
        && white_players[current]->player_type() == human_player)
    {
        input_locked = false;
        return;
    }
}

bool Game::input(unsigned x, unsigned y)
{
    if(input_locked) return false;

    GameOrganizer::CurrentRequest request
        = organizers[current]->current_request();
    bool result;
    switch(request)
    {
        case GameOrganizer::black_te :
        case GameOrganizer::black_remove :
            result = dynamic_cast<HumanPlayer*>(black_players[current])->input(x, y);
            if(result) input_locked = true;
            return result;
        case GameOrganizer::white_te :
        case GameOrganizer::white_remove :
            result = dynamic_cast<HumanPlayer*>(white_players[current])->input(x, y);
            if(result) input_locked = true;
            return result;
        default: break;
    }
    return false;
}

bool Game::input(bool _exchange_choice)
{
    if(input_locked) return false;

    GameOrganizer::CurrentRequest request
        = organizers[current]->current_request();
    bool result;
    switch(request)
    {
        case GameOrganizer::black_exchange :
            result
                = dynamic_cast<HumanPlayer*>(black_players[current])
                    ->input(_exchange_choice);
            if(result) input_locked = true;
            return result;
        case GameOrganizer::white_exchange :
            result
                = dynamic_cast<HumanPlayer*>(white_players[current])
                    ->input(_exchange_choice);
            if(result) input_locked = true;
            return result;
        default: break;
    }
    return false;
}
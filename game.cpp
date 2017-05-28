#include "game.h"

Game::Game(const Game& src)
{
    board = new Board(*(src.board));
    judge = src.judge->clone();
    black_player = src.black_player->clone();
    white_player = src.white_player->clone();
    return;
}

Game::~Game()
{
    if(board) delete board;
    if(judge) delete judge;
    if(black_player) delete black_player;
    if(white_player) delete white_player;
    return;
}

void Game::exchange_player()
{
    Player *temp = black_player;
    black_player = white_player;
    white_player = temp;
    if(black_player) black_player->set_stone(Player::black);
    if(white_player) white_player->set_stone(Player::white);
    return;
}

void Game::set_board(const Board *src)
{
    if(board) delete board;
    board = new Board(*src);
    // Notify the judge
    if(judge) judge->set_board(board);
    // Notify the players
    if(black_player) black_player->set_board(board);
    if(white_player) white_player->set_board(board);
    return;
}

void Game::set_judge(const WinningJudge *src)
{
    if(judge) delete judge;
    judge = src->clone();
    if(board) judge->set_board(board);
    // Notify the players that the judge has changed.
    AIPlayer *aiplayer = NULL;
    if((aiplayer = dynamic_cast<AIPlayer*>(black_player)))
        aiplayer->set_judge(judge);
    if((aiplayer = dynamic_cast<AIPlayer*>(white_player)))
        aiplayer->set_judge(judge);
    return;
}

void Game::set_black(const Player *src)
{
    if(black_player) delete black_player;
    black_player = src->clone();
    black_player->set_stone(Player::black);
    if(board) black_player->set_board(board);
    AIPlayer *aiplayer = NULL;
    if((aiplayer = dynamic_cast<AIPlayer*>(black_player)))
        if(judge) aiplayer->set_judge(judge);
    return;
}

void Game::set_white(const Player *src)
{
    if(white_player) delete white_player;
    white_player = src->clone();
    white_player->set_stone(Player::white);
    if(board) white_player->set_board(board);
    AIPlayer *aiplayer = NULL;
    if((aiplayer = dynamic_cast<AIPlayer*>(white_player)))
        if(judge) aiplayer->set_judge(judge);
    return;
}


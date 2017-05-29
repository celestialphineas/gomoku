#include "game_organizer.h"

GameOrganizer::GameOrganizer(const GameOrganizer &src)
{
    board = src.board;
    judge = src.judge;
    black_player = src.black_player;
    white_player = src.white_player;
    current_request_status = invalid;
    return;
}

GameOrganizer::GameOrganizer(Board *_board, WinningJudge *_judge, Player *_black, Player *_white)
{
    board = _board; judge = _judge;
    black_player = _black; white_player = _white;
    return;
}

void GameOrganizer::exchange_player()
{
    Player *temp = black_player;
    black_player = white_player;
    white_player = temp;
    if(black_player) black_player->set_stone(Player::black);
    if(white_player) white_player->set_stone(Player::white);
    return;
}

void GameOrganizer::set_black(Player *player)
{
    black_player = player;
    if(player) black_player->set_stone(Player::black);
    return;
}

void GameOrganizer::set_white(Player *player)
{
    white_player = player;
    if(player) white_player->set_stone(Player::white);
    return;
}
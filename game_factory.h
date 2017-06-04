// Header file of game factory.
#ifndef __GAME_FACTORY_H_
#define __GAME_FACTORY_H_

#include "game.h"
#include "human_player.h"
#include "primary_ai.h"
#include "std_organizer.h"
#include "std_gomoku_judge.h"
#include "free_style_judge.h"

class GameFactory
{
public:
    enum PlayerType {human_player, primary_ai};
    enum GameRule {standard_rule};
    enum GameJudge {free_style_gomoku, standard_gomoku};
    Game *create_game(
        unsigned n_rounds = 1,
        PlayerType player1 = human_player,
        PlayerType player2 = primary_ai,
        GameRule game_rule = standard_rule,
        GameJudge game_judge = standard_gomoku,
        unsigned board_dim_width = 15,
        unsigned board_dim_height = 15);
private:
    static const unsigned max_round_threshold = 50;
    static const unsigned min_board_dim_width_threshold = 6;
    static const unsigned min_board_dim_height_threshold = 6;
    static const unsigned max_board_dim_width_threshold = 25;
    static const unsigned max_board_dim_height_threshold = 25;
};

#endif
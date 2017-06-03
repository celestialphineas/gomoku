#ifndef __GAME_H
#define __GAME_H

#include "board.h"
#include "winning_judge.h"
#include "player.h"

class Game
{
public:
    typedef unsigned PlayerType;
    static const PlayerType ai_player = 1;
    static const PlayerType human_player = 2;
    typedef unsigned PosStatus;
    static const PosStatus accessible = 0;
    static const PosStatus black_stone = 1;
    static const PosStatus white_stone = 2;
    static const unsigned undefined  = 0xffffffff;
    typedef unsigned GameStatus;
    static const GameStatus ongoing = 0;
    static const GameStatus black_wins = 1;
    static const GameStatus white_wins = 2;
    static const GameStatus not_started = 3;

    Game(const Game&);
    ~Game();

    // Related with rounds
    unsigned n_rounds() const {return n_rounds;}
    // The return value starts from 1
    unsigned current_round() const {return current + 1;}
    bool switch_to_round(unsigned round_index);    
    bool next_round_validity() const;
    bool previous_round_validity() const;
    bool switch_to_next_round();
    bool switch_to_previous_round();

    // Related with players
    PlayerType black_player_type() const
        {return black_players[current]->player_type();}
    PlayerType white_player_type() const
        {return white_players[current]->player_type();}
    void exchange_player();
    
    // Related with the board
    unsigned board_width() const {return boards[current]->n_col();}
    unsigned board_height() const {return boards[current]->n_row();}
    PosStatus pos_status(unsigned x, unsigned y) const
        {return boards[current]->get_status(x, y);}
    bool undo() const {return boards[current]->undo();}

    GameStatus current_status() const {return game_statuses[current];}

    // Handle input
    bool input(unsigned x, unsigned y);
    friend class GameFactory;
    
    // Procedual control
    void next();
private:
    // Private constructor to prevent the object created out of the factory.
    Game() {}
    bool input_locked;
    // The current_index is the index of the subgame that allows both the
    // input and output.
    unsigned current;
    // Number of subgames
    unsigned rounds;
    // List of the game status
    GameStatus game_statuses[];
    Board* boards[];
    WinningJudge* judges[];
    Player* black_players[];
    Player* white_players[];
    GameOrganizer* organizers[];
};

#endif
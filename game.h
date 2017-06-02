#ifndef __GAME_H
#define __GAME_H

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

    // Outputs
    unsigned n_rounds() const {return n_rounds;}
    // The return value starts from 1
    unsigned current_subgame_index() const {return observing_index + 1;}

    PlayerType black_player_type() const
        {return black_players[current_round]->player_type();}
    PlayerType white_player_type() const
        {return white_players[current_round]->player_type();}
    
    unsigned board_width() const {return boards[current_round]->n_col();}
    unsigned board_height() const {return boards[current_round]->n_row();}
    PosStatus pos_status(unsigned x, unsigned y) const
        {return boards[current_round]->get_status(x, y);}

    GameStatus

    bool input(unsigned x, unsigned y);
    friend GameFactory;
private:
    bool input_lock;
    // The current_index is the index of the subgame that allows both the
    // input and output.
    unsigned current_round;
    // Number of subgames
    unsigned rounds;
    // List of the game status
    unsigned game_status[];
    Player* white_players[];
    Player* black_players[];
    WinningJudge* judges[];
    Board* boards[];
    GameOrganizer* organizers[];
};

#endif
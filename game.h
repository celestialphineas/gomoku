#ifndef __GAME_H
#define __GAME_H

class Game
{
public:
    
private:
    // The observing_index is the index of the subgame that allows both the
    // input and output.
    unsigned observing_index;
    // Number of subgames
    unsigned n_rounds;
    // List of the game status
    unsigned game_status[];
    Player* white_players[];
    Player* black_players[];
    WinningJudge* judges[];
    Board* boards[];
    GameOrganizer* organizers[];
};

#endif
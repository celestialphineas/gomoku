#ifndef __GAME_H
#define __GAME_H

class Game
{
public:

private:
    unsigned n_rounds;
    unsigned winnings;
    Player* white_players[];
    Player* black_players[];
    WinningJudge* judges[];
    Board* boards[];
    GameOrganizer* organizers[];
};

#endif
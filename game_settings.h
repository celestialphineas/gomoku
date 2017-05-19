#ifndef __GAME_SETTINGS_
#define __GAME_SETTINGS_

class GameSettings
{
public:
    bool exact_five;    // If an exact five is required
    bool renju;         // False for gomoku, true for renju
    GameSettings(bool _exact_five = false, bool _renju = false)
    {
        exact_five = _exact_five; renju = _renju;
    }
};

#endif
// Header file for the board 
#ifndef __BOARD_H_
#define __BOARD_H_

#include <deque>
#include "te.h"
#include "game_settings.h"

class Board
{
public:
    // Options. We use an unsigned integer for the status of each position on
    // the grid.
    typedef unsigned PosStatus;
    static const PosStatus accessible = 0;
    static const PosStatus black_stone = 1;
    static const PosStatus white_stone = 2;
    static const PosStatus undefined  = 0xffffffff;
    // And an integer for the status of a game.
    typedef unsigned GameStatus;
    static const GameStatus ongoing = 0;
    static const GameStatus black_wins = 1;
    static const GameStatus white_wins = 2;
    static const unsigned undef = 0xffffffff;
    // Rule of three
    Board(
        unsigned _n_rows = 19,
        unsigned _n_cols = 19,
        GameSettings *_global_game_settings = NULL);
    ~Board();
    Board(const Board&);
    // Set the settings file
    bool set_global_settings(GameSettings *_game_settings);

    // The black_te and white_te method provides an interface for players to
    // interact with the board.
    bool black_te(unsigned x, unsigned y);  // Return succeed or not.
    bool white_te(unsigned x, unsigned y);  // 
    // The two remove methods are provided to blame the player who has removed 
    // some stone on the board. Also interface for players to interact with the
    // board object.
    bool black_remove(unsigned x, unsigned y); 
    bool white_remove(unsigned x, unsigned y);
    // Interface for reading private properties
    // Get the number of rows or columns
    unsigned n_row() {return n_rows;}
    unsigned n_col() {return n_cols;}
    // Get the status of a position: accessible/black occupied/white occupied
    unsigned get_status(unsigned x, unsigned y);
    // Get the marker coodinates (see private scope below)
    unsigned get_marker1_x() {return marker1_x;}
    unsigned get_marker1_y() {return marker1_y;}
    unsigned get_marker2_x() {return marker2_x;}
    unsigned get_marker2_y() {return marker2_y;}
    // This function is used to judge who wins the game or if the game is 
    // ongoing.
    GameStatus judge();
    // ===== To do: the undo method. =====
private:
    unsigned n_rows;                // Number of rows in the game
    unsigned n_cols;                // Number of columns in the game
    unsigned n_te;                  // Number of te

    PosStatus *board_data;          // The size of the data is 
                                    //(1+n_rows)*(1+n_columns)
    std::deque<Te> game_sequence;   // All te or removes happened in the game

    GameSettings *game_settings;    // Pointer to the global setting
                                    // (if there is one)
    bool using_global_settings;     // And if the global game setting is used
    
    // Below are general functions for a te or a remove on the board.
    // I do this in order to reduce the amount of codes, but keep the interface
    // crispy.
    bool general_te(unsigned x, unsigned y, unsigned stone);
    bool general_remove(unsigned x, unsigned y, unsigned stone);
    // Below are coordinates of the markers (we need markers to indicate the
    // in-row stones on GUI)
    unsigned marker1_x;
    unsigned marker1_y;
    unsigned marker2_x;
    unsigned marker2_y;
    // Free style (renju == false, exact_five == false)
    GameStatus free_style_judge();
    // Just consider the generalized condition...
    // It can be useful to let it independent from the judge algorithm.
    unsigned n_in_row;
};

#endif
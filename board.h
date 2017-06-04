// Header file for the board
// Celestial Phineas @ ZJU
#ifndef __BOARD_H_
#define __BOARD_H_

#include <deque>
#include <vector>
#include "te.h"

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
    typedef unsigned CurrentWinLoss;
    static const CurrentWinLoss ongoing = 0;
    static const CurrentWinLoss black_wins = 1;
    static const CurrentWinLoss white_wins = 2;
    // Rule of three
    Board(unsigned _n_rows = 15, unsigned _n_cols = 15);
    ~Board();
    Board(const Board&);

    struct SelectedRow
    {
        static const unsigned row = 1;
        static const unsigned col = 2;
        static const unsigned diag = 3;
        static const unsigned adiag = 4;
        unsigned begin_x;
        unsigned begin_y;
        std::vector<PosStatus> row_list;
    };
    // Return a SelectedRow from the board.
    std::vector<SelectedRow> *get_rows() const;
    std::vector<SelectedRow> *get_cols() const;
    std::vector<SelectedRow> *get_diags() const;
    std::vector<SelectedRow> *get_adiags() const;

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
    unsigned n_row() const {return n_rows;}
    unsigned n_col() const {return n_cols;}
    // If the board is empty or full
    bool empty() const;
    bool full() const;
    // Get the status of a position: accessible/black occupied/white occupied
    unsigned get_status(unsigned x, unsigned y) const;
    // Get an instance of the latest te
    Te last_te() const {return game_sequence.back();}
    // Get an instance of the entire game process
    std::deque<Te>* get_game_sequence() const
        {return new std::deque<Te>(game_sequence);}
    // Undo, return true for succeed
    bool undo();
private:
    unsigned n_rows;                // Number of rows in the game
    unsigned n_cols;                // Number of columns in the game

    PosStatus *board_data;          // The size of the data is 
                                    //(1+n_rows)*(1+n_columns)
    std::deque<Te> game_sequence;   // All te or removes happened in the game

    // Below are general functions for a te or a remove on the board.
    // I do this in order to reduce the amount of codes, but keep the interface
    // crispy.
    bool general_te(unsigned x, unsigned y, unsigned stone);
    bool general_remove(unsigned x, unsigned y, unsigned stone);
    unsigned max_id;
};

#endif
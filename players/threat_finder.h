#ifndef __THREAT_FINDER_H_
#define __THREAT_FINDER_H_

#include <cstdlib>
#include <vector>
#include "../board.h"

// The threat finder is used to find threats on a board. The threat finder
// returns a list of Threat class instances to mark the threats and indicate the
// corresponding key positions concerned in the threat.
class ThreatFinder
{
public:
    struct Threat
    {
        static const bool black = false;
        static const bool white = true;
        bool threat_src;
        // The coordinates below are positions to locate the threat.
        unsigned pos1_x;
        unsigned pos1_y;
        unsigned pos2_x;
        unsigned pos2_y;
        // The list is used to record all the key positions (positions that are
        // possibly to solve the threat), the list is a vector consists of vectors
        // of unsigned values to hold the x and y coordinates.
        std::vector<std::vector<unsigned> > key_pos_list;
    };
    static const bool black = false;
    static const bool white = true;
    ThreatFinder(const Board *_board) {board = _board;}
    ThreatFinder(const ThreatFinder &src) {board = src.board;}
    ThreatFinder &operator=(const ThreatFinder &src)
        {return *(new ThreatFinder(src));}
    ~ThreatFinder() {return;}
    void set_board(Board *_board) {board = _board;}
    // This finds the straight in-row stones. 
    // In Chinese gomoku terms, this is called "huo".
    // e.g. A straight three = "huosan"
    //      A straight four  = "huosi"
    // In gomoku games, a "straight three" is an in-row series of
    // [] x x x [], where [] denotes an empty cross on the board, and x denotes
    // a black stone or a white stone.
    //  o x x x [] is not a straight three, for it has one end blocked by the
    // other player. Both blocked by the other player and by the border of the
    // board should be considered as a non-straight threat.
    // For the function below, it finds a list of threats, the first argument
    // "who" indicates whether to find a threat from the black stone or the
    // white, and the second argument "n" is the number of the straight in-row
    // stones that you are to find.
    std::vector<Threat>* find_straight(bool who, unsigned n) const;
    // This is used to find the in-row stones with one end blocked.
    std::vector<Threat>* find_one_end_blocked(bool who, unsigned n) const;
private:
    const Board *board;
};

#endif
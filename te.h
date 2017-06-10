// Header file for class Te
// Celestial Phineas @ ZJU
// A move in the game of gomoku, or renju is called a "te". 
// This class is used to record either a tie or a remove of stone.
#ifndef __TE_H_
#define __TE_H_

class Te
{
public:
    // Options
    static const bool black = false;
    static const bool white = true;
    static const bool remove = false;
    static const bool te = true;
    // Examples of the use of constructor:
    // Te(2, 3, Te::black, Te::te);
    // - Put a black stone at (2, 3)
    // Te(2, 3, Te::white);
    // - Put a white stone at (2, 3)
    // Te(2, 3, Te::white, Te::remove);
    // - The player using white stone removes a stone at (2, 3)
    Te(int unsigned _x, unsigned _y,
        bool _stone_color, unsigned _id, bool _te_status = true);
    ~Te() {};
    // Copy constructor
    Te(const Te &src);
    Te &operator=(const Te &src){return *(new Te(src));}
    // 
    bool is_te() const {return te_status;}
    bool is_remove() const {return !te_status;}
    bool is_white() const {return stone_color;}
    bool is_black() const {return !stone_color;}
    unsigned x() const {return coord_x;}
    unsigned y() const {return coord_y;}
    unsigned id() const {return stone_id;}
    unsigned set_id(unsigned _stone_id) {return stone_id = _stone_id;}
private:
    bool te_status;     // Either a te or a remove
    bool stone_color;   // The PLAYER's stone color
    unsigned stone_id;  // Id of the stone, 0 for a remove or an invalid te
    unsigned coord_x;   // The x coordinate of the te
    unsigned coord_y;   // The y coordinate of the te
};

#endif
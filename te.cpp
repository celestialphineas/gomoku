#include "te.h"

Te::Te(unsigned _x, unsigned _y,
    bool _stone_color, unsigned _id, bool _te_status)
{
    coord_x = _x; coord_y = _y;
    stone_color = _stone_color;
    te_id = _id;
    te_status = _te_status;
    return;
}

Te::Te(const Te &src)
{
    this->te_status = src.te_status;
    this->stone_color = src.stone_color;
    this->te_id = src.te_id;
    this->coord_x = src.coord_x;
    this->coord_y = src.coord_y;
}
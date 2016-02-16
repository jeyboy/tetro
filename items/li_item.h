#ifndef LI_ITEM
#define LI_ITEM

#include "tetro_item.h"

class LiItem : public TetroItem {

//     ----
//     |  |
//     |  |
//     |  |
// ----   |
// |      |
// --------

public:
    LiItem(QGraphicsItem * parent = 0) : TetroItem(parent, QColor::fromRgb(0, 78, 228, 128)) {
        TetroPart * item = new TetroPart(this);
        item -> setRect(1, 0, 1, 1);

        item = new TetroPart(this);
        item -> setRect(1, 1, 1, 1);

        item = new TetroPart(this);
        item -> setRect(1, 2, 1, 1);

        item = new TetroPart(this);
        item -> setRect(0, 2, 1, 1);

        setCentering();
    }
};

#endif // LI_ITEM

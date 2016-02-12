#ifndef LI_REV_ITEM
#define LI_REV_ITEM

#include "tetro_item.h"

class LiRevItem : public TetroItem {

// ----
// |  |
// |  |
// |  |
// |   ----
// |      |
// --------

public:
    LiRevItem(QGraphicsItem * parent = 0) : TetroItem(parent) {
        TetroPart * item = new TetroPart(this);
        item -> setRect(0, 0, 1, 1);
        item -> setPen(pen);

        item = new TetroPart(this);
        item -> setRect(0, 1, 1, 1);
        item -> setPen(pen);

        item = new TetroPart(this);
        item -> setRect(0, 2, 1, 1);
        item -> setPen(pen);

        item = new TetroPart(this);
        item -> setRect(1, 2, 1, 1);
        item -> setPen(pen);

        setCentering();
    }
};

#endif // LI_REV_ITEM

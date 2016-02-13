#ifndef ZU_REV_ITEM
#define ZU_REV_ITEM

#include "tetro_item.h"

class ZuRevItem : public TetroItem {

//     --------
//     |      |
//     |  |----
//     |  |
// -----  |
// |      |
// --------

public:
    ZuRevItem(QGraphicsItem * parent = 0) : TetroItem(parent) {
        TetroPart * item = new TetroPart(this);
        item -> setRect(2, 0, 1, 1);

        item = new TetroPart(this);
        item -> setRect(1, 0, 1, 1);

        item = new TetroPart(this);
        item -> setRect(1, 1, 1, 1);

        item = new TetroPart(this);
        item -> setRect(0, 1, 1, 1);

        setCentering();
    }
};

#endif // ZU_REV_ITEM

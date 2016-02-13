#ifndef ZU_ITEM
#define ZU_ITEM

#include "tetro_item.h"

class ZuItem : public TetroItem {

// --------
// |      |
// ----|  |
//     |  |
//     |  -----
//     |      |
//     --------

public:
    ZuItem(QGraphicsItem * parent = 0) : TetroItem(parent) {
        TetroPart * item = new TetroPart(this);
        item -> setRect(0, 0, 1, 1);

        item = new TetroPart(this);
        item -> setRect(1, 0, 1, 1);

        item = new TetroPart(this);
        item -> setRect(1, 1, 1, 1);

        item = new TetroPart(this);
        item -> setRect(2, 1, 1, 1);

        setCentering();
    }
};

#endif // ZU_ITEM

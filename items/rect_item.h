#ifndef RECT_ITEM
#define RECT_ITEM

#include "tetro_item.h"

class RectItem : public TetroItem {

// --------
// |      |
// |      |
// |      |
// --------

public:
    RectItem(QGraphicsItem * parent = 0) : TetroItem(parent, QColor::fromRgb(228, 222, 0, 128)) {
        TetroPart * item = new TetroPart(this);
        item -> setRect(0, 0, 1, 1);

        item = new TetroPart(this);
        item -> setRect(1, 0, 1, 1);

        item = new TetroPart(this);
        item -> setRect(1, 1, 1, 1);

        item = new TetroPart(this);
        item -> setRect(0, 1, 1, 1);

        setCentering();
    }
};

#endif // RECT_ITEM

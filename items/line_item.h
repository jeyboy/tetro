#ifndef LINE_ITEM
#define LINE_ITEM

#include "tetro_item.h"

class LineItem : public TetroItem {

// ----
// |  |
// |  |
// |  |
// |  |
// |  |
// |  |
// ----

public:
    LineItem(QGraphicsItem * parent = 0) : TetroItem(parent) {
        TetroPart * item = new TetroPart(this);
        item -> setRect(0, 0, 1, 1);

        item = new TetroPart(this);
        item -> setRect(0, 1, 1, 1);

        item = new TetroPart(this);
        item -> setRect(0, 2, 1, 1);

        item = new TetroPart(this);
        item -> setRect(0, 3, 1, 1);

        setCentering();
    }
};

#endif // LINE_ITEM

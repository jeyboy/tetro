#ifndef TI_ITEM
#define TI_ITEM

#include "tetro_item.h"

class TiItem : public TetroItem {

// ------------
// |          |
// ----    ----
//     |  |
//     |  |
//     ----

public:
    TiItem(QGraphicsItem * parent = 0) : TetroItem(parent, QColor::fromRgb(156, 19, 228, 128)) {
        TetroPart * item = new TetroPart(this);
        item -> setRect(0, 0, 1, 1);

        item = new TetroPart(this);
        item -> setRect(1, 0, 1, 1);

        item = new TetroPart(this);
        item -> setRect(2, 0, 1, 1);

        item = new TetroPart(this);
        item -> setRect(1, 1, 1, 1);

        setCentering();
    }
};

#endif // TI_ITEM

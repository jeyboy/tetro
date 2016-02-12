#ifndef BLOCK_ITEM
#define BLOCK_ITEM

#include "tetro_item.h"

// ----
// |  |
// ----

class BlockItem : public TetroItem {
public:
    BlockItem(QGraphicsItem * parent = 0) : TetroItem(parent) {
//        QVector<QPointF> points;
//        points << QPointF(0, 0) * GRANULARITY << QPointF(1, 0) * GRANULARITY <<
//                  QPointF(1, 1) * GRANULARITY << QPointF(0, 1) * GRANULARITY;

        TetroPart * item = new TetroPart(this);
        item -> setRect(0, 0, 1, 1);
        item -> setPen(pen);
        item -> setBrush(QBrush(QColor::fromRgb(24, 24, 24)));
    }
};

#endif // BLOCK_ITEM

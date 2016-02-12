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

        QGraphicsRectItem * item = new QGraphicsRectItem(this);
        item -> setRect(0, 0, GRANULARITY, GRANULARITY);
        item -> setPen(pen);
        setBrush(QBrush(QColor::fromRgb(24, 24, 24))); // not worked
    }
};

#endif // BLOCK_ITEM

#ifndef BLOCK_ITEM
#define BLOCK_ITEM

#include "tetro_item.h"

// ----
// |  |
// ----

class BlockItem : public TetroItem {
public:
    BlockItem(QGraphicsItem * parent = 0) : TetroItem(parent) {
        QVector<QPointF> points;
//        points << QPointF(0, 0) * GRANULARITY << QPointF(1, 0) * GRANULARITY <<
//                  QPointF(1, 1) * GRANULARITY << QPointF(0, 1) * GRANULARITY;
        points << QPointF(0, 0) * GRANULARITY + QPointF(1, 1) << QPointF(1, 0) * GRANULARITY - QPointF(1, 1) <<
                  QPointF(1, 1) * GRANULARITY - QPointF(1, 1) << QPointF(0, 1) * GRANULARITY + QPointF(1, -1);

        setBrush(QBrush(QColor::fromRgb(24, 24, 24, 128)));
        setPolygon(QPolygonF(points));
    }
};

#endif // BLOCK_ITEM

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
        QVector<QPointF> points;
        points << QPointF(0, 0) * GRANULARITY << QPointF(1, 0) * GRANULARITY <<
                  QPointF(1, 2) * GRANULARITY << QPointF(2, 2) * GRANULARITY <<
                  QPointF(2, 3) * GRANULARITY << QPointF(0, 3) * GRANULARITY;

        setPolygon(QPolygonF(points));
    }
};

#endif // LI_REV_ITEM

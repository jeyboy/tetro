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
    TiItem(QGraphicsItem * parent = 0) : TetroItem(parent) {
        QVector<QPointF> points;
        points << QPointF(0, 0) * GRANULARITY << QPointF(3, 0) * GRANULARITY <<
                  QPointF(3, 1) * GRANULARITY << QPointF(2, 1) * GRANULARITY <<
                  QPointF(2, 2) * GRANULARITY << QPointF(1, 2) * GRANULARITY <<
                  QPointF(1, 1) * GRANULARITY << QPointF(0, 1) * GRANULARITY;

        setPolygon(QPolygonF(points));
    }
};

#endif // TI_ITEM

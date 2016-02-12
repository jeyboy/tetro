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
    RectItem(QGraphicsItem * parent = 0) : TetroItem(parent) {
        QVector<QPointF> points;
        points << QPointF(0, 0) * GRANULARITY << QPointF(2, 0) * GRANULARITY <<
                  QPointF(2, 2) * GRANULARITY << QPointF(0, 2) * GRANULARITY;

        setPolygon(QPolygonF(points));
    }
};

#endif // RECT_ITEM

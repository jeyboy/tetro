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
        QVector<QPointF> points;
        points << QPointF(0, 0) * GRANULARITY << QPointF(1, 0) * GRANULARITY <<
                  QPointF(1, 4) * GRANULARITY << QPointF(0, 4) * GRANULARITY;

        setPolygon(QPolygonF(points));
    }
};

#endif // LINE_ITEM

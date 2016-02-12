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
//        QVector<QPointF> points;
//        points << QPointF(0, 0) * GRANULARITY << QPointF(2, 0) * GRANULARITY <<
//                  QPointF(2, 2) * GRANULARITY << QPointF(0, 2) * GRANULARITY;

        QGraphicsRectItem * item = new QGraphicsRectItem(this);
        item -> setRect(0, 0, GRANULARITY, GRANULARITY);
        item -> setPen(pen);

        item = new QGraphicsRectItem(this);
        item -> setRect(GRANULARITY, 0, GRANULARITY, GRANULARITY);
        item -> setPen(pen);

        item = new QGraphicsRectItem(this);
        item -> setRect(GRANULARITY, GRANULARITY, GRANULARITY, GRANULARITY);
        item -> setPen(pen);

        item = new QGraphicsRectItem(this);
        item -> setRect(0, GRANULARITY, GRANULARITY, GRANULARITY);
        item -> setPen(pen);

        setCentering();
    }
};

#endif // RECT_ITEM

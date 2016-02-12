#ifndef ZU_REV_ITEM
#define ZU_REV_ITEM

#include "tetro_item.h"

class ZuRevItem : public TetroItem {

//     --------
//     |      |
//     |  |----
//     |  |
// -----  |
// |      |
// --------

public:
    ZuRevItem(QGraphicsItem * parent = 0) : TetroItem(parent) {
//        QVector<QPointF> points;
//        points << QPointF(1, 0) * GRANULARITY << QPointF(3, 0) * GRANULARITY <<
//                  QPointF(3, 1) * GRANULARITY << QPointF(2, 1) * GRANULARITY <<
//                  QPointF(2, 2) * GRANULARITY << QPointF(0, 2) * GRANULARITY <<
//                  QPointF(0, 1) * GRANULARITY << QPointF(1, 1) * GRANULARITY;

        QGraphicsRectItem * item = new QGraphicsRectItem(this);
        item -> setRect(2 * GRANULARITY, 0, GRANULARITY, GRANULARITY);
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

#endif // ZU_REV_ITEM

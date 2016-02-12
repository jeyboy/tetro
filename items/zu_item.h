#ifndef ZU_ITEM
#define ZU_ITEM

#include "tetro_item.h"

class ZuItem : public TetroItem {

// --------
// |      |
// ----|  |
//     |  |
//     |  -----
//     |      |
//     --------

public:
    ZuItem(QGraphicsItem * parent = 0) : TetroItem(parent) {
//        QVector<QPointF> points;
//        points << QPointF(0, 0) * GRANULARITY << QPointF(2, 0) * GRANULARITY <<
//                  QPointF(2, 1) * GRANULARITY << QPointF(3, 1) * GRANULARITY <<
//                  QPointF(3, 2) * GRANULARITY << QPointF(1, 2) * GRANULARITY <<
//                  QPointF(1, 1) * GRANULARITY << QPointF(0, 1) * GRANULARITY;

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
        item -> setRect(2 * GRANULARITY, GRANULARITY, GRANULARITY, GRANULARITY);
        item -> setPen(pen);

        setCentering();
    }
};

#endif // ZU_ITEM

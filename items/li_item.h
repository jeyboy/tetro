#ifndef LI_ITEM
#define LI_ITEM

#include "tetro_item.h"

class LiItem : public TetroItem {

//     ----
//     |  |
//     |  |
//     |  |
// ----   |
// |      |
// --------

public:
    LiItem(QGraphicsItem * parent = 0) : TetroItem(parent) {
//        QVector<QPointF> points;
//        points << QPointF(1, 0) * GRANULARITY << QPointF(2, 0) * GRANULARITY <<
//                  QPointF(2, 3) * GRANULARITY << QPointF(0, 3) * GRANULARITY <<
//                  QPointF(0, 2) * GRANULARITY << QPointF(1, 2) * GRANULARITY;

        QGraphicsRectItem * item = new QGraphicsRectItem(this);
        item -> setRect(GRANULARITY, 0, GRANULARITY, GRANULARITY);
        item -> setPen(pen);

        item = new QGraphicsRectItem(this);
        item -> setRect(GRANULARITY, GRANULARITY, GRANULARITY, GRANULARITY);
        item -> setPen(pen);

        item = new QGraphicsRectItem(this);
        item -> setRect(GRANULARITY, 2 * GRANULARITY, GRANULARITY, GRANULARITY);
        item -> setPen(pen);

        item = new QGraphicsRectItem(this);
        item -> setRect(0, 2 * GRANULARITY, GRANULARITY, GRANULARITY);
        item -> setPen(pen);

        setCentering();
    }
};

#endif // LI_ITEM

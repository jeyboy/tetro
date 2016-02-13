#ifndef TETRO_ITEM
#define TETRO_ITEM

#include <qhash.h>
#include <qevent.h>
#include <qpen.h>
#include <qdebug.h>

#include "tetro_part.h"

class TetroItem : public QGraphicsRectItem {
protected:
    void rotate(qreal angle) { setRotation(rotation() + angle); }
public:
    TetroItem(QGraphicsItem * parent = 0) : QGraphicsRectItem(parent) {
        setPen(QPen(QBrush(QColor::fromRgb(0,0,0)), 2));
    }

    void setGridPos(int x, int y, bool xcentering = false) {
        if (xcentering) {
            QSizeF isize = childrenBoundingRect().size() / GRANULARITY;
            x -= (int)isize.width() / 2/* - ((int)isize.width() % 2)*/;
            x = qMax(0, x);
        }

        setPos(x * GRANULARITY, y * GRANULARITY);
    }

    void pushUp() { setPos(pos() - QPointF(0, GRANULARITY)); }
    void pushDown() { setPos(pos() + QPointF(0, GRANULARITY)); }
    void pushLeft() { setPos(pos() - QPointF(GRANULARITY, 0)); }
    void pushRight() { setPos(pos() + QPointF(GRANULARITY, 0)); }

    void rotateClockwise() { rotate(90); }
    void rotateCounterClockwise() { rotate(-90); }

    void setCentering() {
        QPointF center = childrenBoundingRect().center();
        QPointF offset((int)center.x() % GRANULARITY, (int)center.y() % GRANULARITY);
        setTransformOriginPoint(center + offset);
    }

    QRectF itemRect() const {
        return childrenBoundingRect().translated(pos());
    }
};

#endif // TETRO_ITEM

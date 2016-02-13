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
    enum ItemAngle {
        random = -1,
        foward = 0,
        left = 90,
        bottom = 180,
        right = 270
    };

    TetroItem(QGraphicsItem * parent = 0, ItemAngle angle = random) : QGraphicsRectItem(parent) {
        setPen(QPen(QBrush(QColor::fromRgb(0,0,0)), 2));

        if (angle == random) angle = (ItemAngle)((qrand() % 5) * 90);
        setRotation((int)angle);
    }

    void setGridPos(int x, int y, bool centering = false) {
        if (centering) {
            QRectF rect = childrenBoundingRect();
            QSizeF isize = rect.size() / GRANULARITY;
            x -= (int)isize.width() / 2;
            x = qMax(0, x);
            y = qMax(0, y);
            if (rect.top() < 0)
                y = 0;
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

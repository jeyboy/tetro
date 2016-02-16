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

    TetroItem(QGraphicsItem * parent = 0, const QColor & color = QColor(0,0,0,0)) : QGraphicsRectItem(parent) {
        setPen(QPen(QBrush(QColor::fromRgb(0,0,0)), 2));
        setBrush(QBrush(color));
    }

    void setGridPos(int x, int y, bool centering = false) {
        if (centering) {
            QRectF rect = sceneChildrenBoundingRect();
            QSizeF isize = rect.size() / GRANULARITY;
            x -= (int)isize.width() / 2;
            x = qMax(0, x);
            y = qMax(0, y);

            // remove rotation offset movement
            if (rect.top() < GRANULARITY)
                y += 1;
            else if (rect.top() > GRANULARITY + 1)
                y -= (rect.top() - GRANULARITY + 1) / GRANULARITY;
        }

        setPos(x * GRANULARITY, y * GRANULARITY);
    }

    void pushUp() { setPos(pos() - QPointF(0, GRANULARITY)); }
    void pushDown() { setPos(pos() + QPointF(0, GRANULARITY)); }
    void pushLeft() { setPos(pos() - QPointF(GRANULARITY, 0)); }
    void pushRight() { setPos(pos() + QPointF(GRANULARITY, 0)); }

    void rotateClockwise() { rotate(90); }
    void rotateCounterClockwise() { rotate(-90); }
    void rotate(ItemAngle angle) {
        if (angle == random) angle = (ItemAngle)((qrand() % 5) * 90);
        setRotation((int)angle);
    }

    void setCentering() {
        QPointF center = childrenBoundingRect().center();
        setTransformOriginPoint(center);
    }

    QRectF sceneChildrenBoundingRect() {
        QRectF res;

        QList<QGraphicsItem *> children = childItems();

        for(QList<QGraphicsItem *>::Iterator ch = children.begin(); ch != children.end(); ch++) {
            res |= (*ch) -> sceneBoundingRect();
        }

        return res;
    }
};

#endif // TETRO_ITEM

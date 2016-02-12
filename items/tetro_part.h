#ifndef TETRO_PART
#define TETRO_PART

#include <qgraphicsitem.h>

#define GRANULARITY 24

class TetroPart : public QGraphicsRectItem {
public:
    TetroPart(QGraphicsItem * parent = 0) : QGraphicsRectItem(parent) {

    }

    void setRect(qreal ax, qreal ay, qreal w, qreal h) {
        QGraphicsRectItem::setRect(QRectF(ax * GRANULARITY, ay * GRANULARITY, w * GRANULARITY, h * GRANULARITY));
    }

    QPointF gridPos() {
        return (scenePos() + mapToParent(rect().topLeft())) / GRANULARITY;
    }
};

#endif // TETRO_PART

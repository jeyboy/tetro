#ifndef TETRO_PART
#define TETRO_PART

#include <qgraphicsitem.h>
#include <qpainter.h>

#define GRANULARITY 24

class TetroPart : public QGraphicsRectItem {
public:
    TetroPart(QGraphicsItem * parent = 0) : QGraphicsRectItem(parent) {
        setPen(QPen(QBrush(QColor::fromRgb(0,0,0)), 2));
    }

    void paint(QPainter * painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/ = 0) {
        QGraphicsRectItem * parent = (QGraphicsRectItem *)parentItem();

        painter -> setPen(parent ? parent -> pen() : pen());
        painter -> setBrush(parent ? parent -> brush() : brush());
        painter -> drawRoundedRect(boundingRect(), 4, 4);
    }

    void setRect(qreal ax, qreal ay, qreal w, qreal h) {
        QGraphicsRectItem::setRect(QRectF(ax * GRANULARITY + 2, ay * GRANULARITY + 2, w * GRANULARITY - 4, h * GRANULARITY - 4));
    }

    void setGridPos(QPoint pos) { setRect(pos.x(), pos.y(), 1, 1); }
    void iterateGridPos(QPoint iter) { setGridPos(gridPos().toPoint() + iter); }

    QPointF gridPos() { return sceneBoundingRect().topLeft() / GRANULARITY; }
};

#endif // TETRO_PART

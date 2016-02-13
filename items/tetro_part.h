#ifndef TETRO_PART
#define TETRO_PART

#include <qgraphicsitem.h>
#include <qpainter.h>

#define GRANULARITY 24

class TetroPart : public QGraphicsRectItem {
public:
    TetroPart(QGraphicsItem * parent = 0) : QGraphicsRectItem(parent) {}

    void paint(QPainter * painter, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/ = 0) {
        painter -> setPen(pen());
        painter -> setBrush(brush());
        painter -> drawRoundedRect(boundingRect(), 4, 4);
    }

    void setRect(qreal ax, qreal ay, qreal w, qreal h) {
        QGraphicsRectItem::setRect(QRectF(ax * GRANULARITY + 2, ay * GRANULARITY + 2, w * GRANULARITY - 4, h * GRANULARITY - 4));
    }

    void setGridPos(QPointF pos) { setRect(pos.x(), pos.y(), 1, 1); }
    void iterateGridPos(QPointF iter) { setGridPos(gridPos() + iter); }

    QPointF gridPos() { return sceneBoundingRect().topLeft() / GRANULARITY; }
};

#endif // TETRO_PART

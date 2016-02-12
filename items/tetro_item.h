#ifndef TETRO_ITEM
#define TETRO_ITEM

#include <qgraphicsitem.h>
#include <qevent.h>
#include <qpen.h>
#include <qdebug.h>

#define GRANULARITY 24

class TetroItem : public QGraphicsPolygonItem {
protected:
    void keyPressEvent(QKeyEvent * event) {
        switch(event -> key()) {
            case Qt::Key_Left: {
                setPos(pos() - QPointF(GRANULARITY, 0));
            break;}

            case Qt::Key_Right: {
                setPos(pos() + QPointF(GRANULARITY, 0));
            break;}

            case Qt::Key_Down: {
                setPos(pos() + QPointF(0, GRANULARITY));
            break;}

            case Qt::Key_Space: {
                setRotation(rotation() + 90);
            break;}

            default: ;
        }
    }
public:
    TetroItem(QGraphicsItem * parent = 0) : QGraphicsPolygonItem(parent) {
        setPen(QPen(QBrush(QColor::fromRgb(0,0,0)), 3));
    }

    void setPolygon(const QPolygonF & polygon) {
        QGraphicsPolygonItem::setPolygon(polygon);
        setTransformOriginPoint(polygon.boundingRect().center() + QPointF(GRANULARITY / 2, 0));
    }

    bool isIntersectedLevel(int level) {
        return itemRect().bottom() / GRANULARITY >= level;
    }

    QRectF itemRect() const {
        return QRectF(pos(), polygon().boundingRect().size());
    }
};

#endif // TETRO_ITEM

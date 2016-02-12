#ifndef TETRO_ITEM
#define TETRO_ITEM

#include <qhash.h>
#include <qgraphicsitem.h>
#include <qevent.h>
#include <qpen.h>
#include <qdebug.h>

#define GRANULARITY 24

class TetroItem : public QGraphicsRectItem {
protected:
public:
    QPen pen;

    TetroItem(QGraphicsItem * parent = 0) : QGraphicsRectItem(parent) {
        pen = QPen(QBrush(QColor::fromRgb(0,0,0)), 2);
    }

    void rotate(qreal angle) { setRotation(rotation() + angle); }

    void setCentering() {
        QPointF center = childrenBoundingRect().center();
        QPointF offset((int)center.x() % GRANULARITY, (int)center.y() % GRANULARITY);
        setTransformOriginPoint(center + offset);
    }

//    void setPolygon(const QPolygonF & polygon) {
//        QGraphicsPolygonItem::setPolygon(polygon);
//        setTransformOriginPoint(polygon.boundingRect().center() + QPointF(GRANULARITY / 2, 0));
//    }

//    bool isIntersectedLevel(int level) {
//        return itemRect().bottom() / GRANULARITY >= level;
//    }

//    QPolygonF scenePolygon() {
////        return mapToScene(polygon());
//    }

    QRectF itemRect() const {
        return childrenBoundingRect().translated(pos());
    }
};

#endif // TETRO_ITEM

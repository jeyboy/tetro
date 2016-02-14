#ifndef ROTATION_CONTAINER
#define ROTATION_CONTAINER

#include <qgraphicsitem.h>

class RotationContainer : public QGraphicsObject {
    Q_OBJECT
public:
    RotationContainer() { }

    QRectF boundingRect() const { return QRectF();/*childrenBoundingRect();*/ }

    void paint(QPainter * /*painter*/, const QStyleOptionGraphicsItem * /*option*/, QWidget * /*widget*/ = 0) {}
};

#endif // ROTATION_CONTAINER

#ifndef TETRO_SCENE
#define TETRO_SCENE

#include <qpainter.h>
#include <qgraphicsscene.h>

class TetroScene : public QGraphicsScene {
    int granularity;
protected:
    void drawBackground(QPainter * painter, const QRectF & rect) {
        qreal left = int(rect.left()) - (int(rect.left()) % granularity);
        qreal top = int(rect.top()) - (int(rect.top()) % granularity);

        QVarLengthArray<QLineF, 100> lines;

        for (qreal x = left; x < rect.right(); x += granularity)
            lines.append(QLineF(x, rect.top(), x, rect.bottom()));
        for (qreal y = top; y < rect.bottom(); y += granularity)
            lines.append(QLineF(rect.left(), y, rect.right(), y));

        painter -> setPen(QColor::fromRgb(148, 148, 148, 32));
        painter -> drawLines(lines.data(), lines.size());

        QGraphicsScene::drawBackground(painter, rect);
    }

public:
    TetroScene(int granularity, QObject * parent = 0) : QGraphicsScene(parent), granularity(granularity) {

    }
};

#endif // TETRO_SCENE

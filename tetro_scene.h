#ifndef TETRO_SCENE
#define TETRO_SCENE

//#include <math.h>
#include <qtimer.h>
#include <qpainter.h>
#include <qgraphicsscene.h>
//#include <qpropertyanimation.h>
//#include <qgraphicseffect.h>

#include "items/index.h"

#define DEFAULT_SPEED 500

class TetroScene : public QGraphicsScene {
    Q_OBJECT

    enum ItemTypes {
        block_item = -2,
        random_item = -1,
        rect_item = 0,
        li_item,
        li_rev_item,
        line_item,
        ti_item,
        zu_item,
        zu_rev_item
    };

    QTimer * timer;
    TetroItem * active;
    QList<QVector<bool> > places;
    int start_x_pos, end_x_pos, end_y_pos;
protected slots:
    void onTimer() {
        if (active == 0) {
            active = generateItem();
            addItem(active);
            active -> setPos(start_x_pos * GRANULARITY, 0);
            active -> setFlag(QGraphicsItem::ItemIsFocusable, true);
            active -> setFocus();
        }
        else {
            if (checkCollision()) {
                QList<QGraphicsItem *> children = active -> childItems();
                for(QList<QGraphicsItem *>::Iterator ch = children.begin(); ch != children.end(); ch++) {
                    QPointF point = (*ch) -> scenePos();
                    places[point.x() / GRANULARITY][point.y() / GRANULARITY] = true;
                }
                active = 0;
                onTimer();
            }
            else active -> setPos(active -> pos() + QPointF(0, GRANULARITY));
        }
    }
protected:
    void drawBackground(QPainter * painter, const QRectF & rect) {
        qreal left = int(rect.left()) - (int(rect.left()) % GRANULARITY);
        qreal top = int(rect.top()) - (int(rect.top()) % GRANULARITY);

        QVarLengthArray<QLineF, 100> lines;

        for (qreal x = left; x < rect.right(); x += GRANULARITY)
            lines.append(QLineF(x, rect.top(), x, rect.bottom()));
        for (qreal y = top; y < rect.bottom(); y += GRANULARITY)
            lines.append(QLineF(rect.left(), y, rect.right(), y));

        painter -> setPen(QColor::fromRgb(148, 148, 148, 32));
        painter -> drawLines(lines.data(), lines.size());

        QGraphicsScene::drawBackground(painter, rect);
    }

    void keyPressEvent(QKeyEvent * event) {
        if (active) {
            switch(event -> key()) {
                case Qt::Key_Left: {
                    active -> setPos(active -> pos() - QPointF(GRANULARITY, 0));
                    if (checkCollision())
                        active -> setPos(active -> pos() + QPointF(GRANULARITY, 0));
                break;}

                case Qt::Key_Right: {
                    active -> setPos(active -> pos() + QPointF(GRANULARITY, 0));
                    if (checkCollision())
                        active -> setPos(active -> pos() - QPointF(GRANULARITY, 0));
                break;}

                case Qt::Key_Down: {
                    active -> setPos(active -> pos() + QPointF(0, GRANULARITY));
                    if (checkCollision())
                        active -> setPos(active -> pos() - QPointF(0, GRANULARITY));
                break;}

                case Qt::Key_Space: {
                    active -> rotate(90);
                    if (checkCollision())
                        active -> rotate(-90);
                break;}

                default: ;
            }
        }
    }

    bool checkCollision() {
//        TetroItem * item = new TetroItem();
//        item -> setPolygon(active -> scenePolygon());
//        item -> setBrush(QBrush(Qt::black));
//        addItem(item);

        QList<QGraphicsItem *> children = active -> childItems();
        for(QList<QGraphicsItem *>::Iterator ch = children.begin(); ch != children.end(); ch++) {
            QPointF point = (*ch) -> scenePos() / GRANULARITY;
            qDebug() << "CHECK" << (*ch) -> scenePos() << point << end_x_pos << end_y_pos;
            if (point.x() < 0 || point.x() >= end_x_pos) return true;
            if (point.y() >= end_y_pos) return true;
            if (places[point.x()][point.y()])
                return true;
        }

        return false;
    }

    TetroItem * generateItem(ItemTypes i = random_item) {
         //(qrand() % (max-min)+1) + min
        if (i == random_item) i = (ItemTypes)(qrand() % 7);

        switch(i) {
            case block_item: return new BlockItem();
            case rect_item: return new RectItem();
            case li_item: return new LiItem();
            case li_rev_item: return new LiRevItem();
            case line_item: return new LineItem();
            case ti_item: return new TiItem();
            case zu_item: return new ZuItem();
            case zu_rev_item: return new ZuRevItem();
            default:
                qDebug() << "PI";
                return new RectItem();
        }
    }
public:
    TetroScene(int width, int height, QObject * parent = 0) : QGraphicsScene(parent), active(0) {
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));

        setSceneRect(0, 0, width, height);
        end_x_pos = width / GRANULARITY;
        start_x_pos = end_x_pos / 2;
        end_y_pos = height / GRANULARITY;

        for(int i = 0; i < end_x_pos; i++)
            places.append(QVector<bool>().fill(false, end_y_pos));
    }

    void startTimer() {
        timer -> start(DEFAULT_SPEED);
        onTimer();
    }

    void pauseTimer() {
        timer -> stop();
    }
};

#endif // TETRO_SCENE

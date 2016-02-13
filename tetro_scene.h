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
    QList<QVector<TetroPart *> > places;
    int start_x_pos, end_x_pos, end_y_pos;
protected slots:
    void onTimer() {
        if (active == 0) {
            active = generateItem(line_item);
            addItem(active);
            active -> setGridPos(start_x_pos, 0, true);
            active -> setFlag(QGraphicsItem::ItemIsFocusable, true);
            active -> setFocus();
        }
        else {
            active -> pushDown();
            if (checkCollision()) {
                pauseTimer();
                active -> pushUp();

                QHash<int, bool> rows;
                {
                    QList<QGraphicsItem *> children = active -> childItems();

                    for(QList<QGraphicsItem *>::Iterator ch = children.begin(); ch != children.end(); ch++) {
                        TetroPart * part = ((TetroPart *)*ch);
                        QPointF point = part -> gridPos();
                        places[point.y()][point.x()] = part;
                        rows.insert(point.y(), false);
                        part -> setParentItem(0);
                        part -> setGridPos(point.toPoint());
                    }
                }

                delete active;
                active = 0;
                removeRows(rows.keys());
                startTimer();
            }
        }
    }
protected:
    void drawBackground(QPainter * painter, const QRectF & rect) {
        QGraphicsScene::drawBackground(painter, rect);

        qreal left = int(rect.left()) - (int(rect.left()) % GRANULARITY);
        qreal top = int(rect.top()) - (int(rect.top()) % GRANULARITY);

        QVarLengthArray<QLineF, 100> lines;

        for (qreal x = left; x < rect.right(); x += GRANULARITY)
            lines.append(QLineF(x, rect.top(), x, rect.bottom()));
        for (qreal y = top; y < rect.bottom(); y += GRANULARITY)
            lines.append(QLineF(rect.left(), y, rect.right(), y));

        painter -> setPen(QColor::fromRgb(148, 148, 148, 32));
        painter -> drawLines(lines.data(), lines.size());
    }

    void keyPressEvent(QKeyEvent * event) {
        if (active) {
            switch(event -> key()) {
                case Qt::Key_Left: {
                    active -> pushLeft();
                    if (checkCollision())
                        active -> pushRight();
                break;}

                case Qt::Key_Right: {
                    active -> pushRight();
                    if (checkCollision())
                        active -> pushLeft();
                break;}

                case Qt::Key_Down: {
                    active -> pushDown();
                    if (checkCollision())
                        active -> pushUp();
                break;}

                case Qt::Key_Space: {
                    active -> rotateClockwise();
                    if (checkCollision())
                        active -> rotateCounterClockwise();
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
            QPointF point = ((TetroPart *)*ch) -> gridPos();
            if (point.x() < 0 || point.x() >= end_x_pos) return true;
            if (point.y() < 0 || point.y() >= end_y_pos) return true;
            if (places[point.y()][point.x()])
                return true;
        }

        return false;
    }

    void removeRows(const QList<int> & rows) {
        int max = -999999;

        QHash<int, int> removed;

        for(QList<int>::ConstIterator y = rows.cbegin(); y != rows.cend(); y++) {
            if (!places[*y].contains(0)) {
                qDeleteAll(places[*y]);
                places[*y] = QVector<TetroPart *>().fill(0, end_x_pos);
                max = qMax(max, *y);
                removed.insert(*y, 1);
            }
        }

        int step = 0;
        if (max != -999999)
            for(int y = max; y > -1; y--) {
                if (removed.contains(y))
                    step += removed.take(y);
                else {
                    QVector<TetroPart *> parts = places[y];
                    for(QVector<TetroPart *>::Iterator part = parts.begin(); part != parts.end(); part++)
                        if ((*part))
                            (*part) -> iterateGridPos(QPoint(0, step));
                    places.swap(y, y + step);
                }
            }
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
        setBackgroundBrush(QBrush(Qt::white));
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));

        setSceneRect(0, 0, width, height);
        end_x_pos = width / GRANULARITY;
        start_x_pos = end_x_pos / 2;
        end_y_pos = height / GRANULARITY;

        for(int i = 0; i < end_y_pos; i++)
            places.append(QVector<TetroPart *>().fill(0, end_x_pos));
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

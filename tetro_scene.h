#ifndef TETRO_SCENE
#define TETRO_SCENE

//#include <math.h>
#include <qtimer.h>
#include <qpainter.h>
#include <qgraphicsscene.h>
#include <qdatetime.h>
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
    QList<QVector<TetroPart *> > places; // change on raw arrays
    int start_x_pos, end_x_pos, end_y_pos;
    int field_width, field_height;
signals:
    void paused();
    void resumed();
    void gameOver();

protected slots:
    void onTimer() {
        if (active == 0)
            insertNewItem();
        else moveItem();
    }
protected:
    void drawBackground(QPainter * painter, const QRectF & rect) {
        QGraphicsScene::drawBackground(painter, rect);
        QVarLengthArray<QLineF, 100> lines;

        qreal limit_x = field_width;
        qreal limit_y = field_height;

        for (qreal x = 0; x < limit_x; x += GRANULARITY)
            lines.append(QLineF(x, 0, x, limit_y));
        for (qreal y = 0; y < limit_y; y += GRANULARITY)
            lines.append(QLineF(0, y, limit_x, y));

        painter -> setPen(QColor::fromRgb(148, 148, 148, 32));
        painter -> drawLines(lines.data(), lines.size());
    }

    void keyPressEvent(QKeyEvent * event) {
        if (event -> key() == Qt::Key_Escape) {
            if (timer -> isActive()) {
                pauseTimer();
                emit paused();
            } else {
                startTimer();
                emit resumed();
            }
        }

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

    void insertNewItem() {
        active = generateItem();
        addItem(active);
        active -> setGridPos(start_x_pos, 0, true);
        active -> setFlag(QGraphicsItem::ItemIsFocusable, true);
        active -> setFocus();

        if (checkCollision())
            emit gameOver();
    }

    void moveItem() {
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

    bool checkCollision() {
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

        qDebug() << "-----------------------------------------";

        QHash<int, int> removed;

        for(QList<int>::ConstIterator y = rows.cbegin(); y != rows.cend(); y++) {
            if (!places[*y].contains(0)) {
                qDebug() << (*y);
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
    TetroScene(int width, int height, QObject * parent = 0) : QGraphicsScene(parent), active(0), field_width(width), field_height(height) {
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
        qsrand(QDateTime::currentMSecsSinceEpoch() / 8);
    }

    void pauseTimer() {
        timer -> stop();
    }
};

#endif // TETRO_SCENE

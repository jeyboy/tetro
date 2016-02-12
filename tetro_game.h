#ifndef TETRO_GAME
#define TETRO_GAME

#include "tetro_scene.h"
#include "items/index.h"

#include <qpropertyanimation.h>
//#include <qgraphicseffect.h>
#include <math.h>
#include <qgraphicsview.h>
#include <qtimer.h>
#include <qlist.h>

#define DEFAULT_SPEED 500
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 771

class TetroGame : public QGraphicsView {
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

    TetroScene * scene;
    QTimer * timer;
    bool inited;
    QHash<TetroItem *, QPolygonF> items;
    TetroItem * active;
    int start_x_pos, end_y_pos;
protected slots:
    void onTimer() {
        if (active == 0) {
            active = generateItem();
            scene -> addItem(active);
            active -> setPos(start_x_pos * GRANULARITY, 0);
            active -> setFlag(QGraphicsItem::ItemIsFocusable, true);
            active -> setFocus();
        }
        else {
            if (checkCollision()) {
                items.insert(active, active -> polygon().translated(active -> pos()));
                active = 0;
                onTimer();
            }
            else active -> setPos(active -> pos() + QPointF(0, GRANULARITY));
        }
    }

protected:
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
                    active -> setRotation(active -> rotation() + 90);
                    if (checkCollision())
                        active -> setRotation(active -> rotation() - 90);
                break;}

                default: ;
            }
        }
    }

    bool checkCollision() {
        bool intersected = false;
        QPolygonF active_poly = active -> polygon().translated(active -> pos() + QPointF(0, GRANULARITY));
        for(QHash<TetroItem *, QPolygonF>::ConstIterator item = items.cbegin(); item != items.cend(); item++)
            if (!item.value().intersected(active_poly).isEmpty()) {
                intersected = true;
                break;
            }

//        qDebug() << intersected << active -> isIntersectedLevel(end_y_pos);
        return (intersected || active -> isIntersectedLevel(end_y_pos));
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
    TetroGame(QWidget * parent = 0) : QGraphicsView(parent), inited(false), active(0) {
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));

        setStyleSheet("border: transparent;");
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);

        scene = new TetroScene(GRANULARITY, this);
        scene -> setSceneRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        setScene(scene);
        start_x_pos = (SCREEN_WIDTH / GRANULARITY) / 2;
        end_y_pos = SCREEN_HEIGHT / GRANULARITY;
    }

    ~TetroGame() {
        pause();
        items.clear();
    }

    void start() {
        if (!inited) {
//            RectItem * item = new RectItem();
//            scene -> addItem(item);
//            items.append(item);
            inited = true;
        }

        timer -> start(DEFAULT_SPEED);
        onTimer();
    }

    void pause() {
        timer -> stop();
    }
};

#endif // TETRO_GAME

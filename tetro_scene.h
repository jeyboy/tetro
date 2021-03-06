#ifndef TETRO_SCENE
#define TETRO_SCENE

#include <math.h>
#include <qtimer.h>
#include <qpainter.h>
#include <qgraphicsscene.h>
#include <qdatetime.h>

#include <qpropertyanimation.h>

//#include <qgraphicseffect.h>

#include "items/index.h"

#define DEFAULT_SPEED 500
#define LEVEL_SPEED 40
#define LINE_POINTS 100

#define BCOLOR QColor::fromRgb(148, 148, 148, 32)

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
    TetroItem * active, * next;
    TextItem * level_text, * score_text, * lines_text, * figures_text;
    QPropertyAnimation * rotateAnimation;
    QList<QPair<QVector<TetroPart *>, int> > places; // change on raw arrays
    int start_x_pos, end_x_pos, end_y_pos;
    int field_width, field_height;
    int level, scores, lines, figures;
    int info_offset_x;
    bool ended;
signals:
    void paused();
    void resumed();
    void gameOver();
    void congratulations();
    void newGame();

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

        painter -> fillRect(0, 0, limit_x, limit_y, Qt::white);
        for (qreal x = 0; x < limit_x; x += GRANULARITY)
            lines.append(QLineF(x, 0, x, limit_y));
        for (qreal y = 0; y < limit_y; y += GRANULARITY)
            lines.append(QLineF(0, y, limit_x, y));

        painter -> setPen(BCOLOR);
        painter -> drawLines(lines.data(), lines.size());
    }

    void keyPressEvent(QKeyEvent * event) {
        if (event -> key() == Qt::Key_Escape) {
            if (ended) {
                reset();
                emit newGame();
                return;
            }

            if (timer -> isActive()) {
                pauseTimer();
                emit paused();
            } else {
                if (active) {
                    startTimer();
                    emit resumed();
                }
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
                    if (checkCollision(true))
                        active -> rotateCounterClockwise();
                break;}

                default: ;
            }
        }
    }

    void fillMatrix() {
        places.clear();
        for(int i = 0; i < end_y_pos; i++)
            places.append(QPair<QVector<TetroPart *>, int>(QVector<TetroPart *>().fill(0, end_x_pos), 0));
    }

    void insertNewItem() {
        if (!next) {
            active = generateItem();
            addItem(active);
            active -> rotate(TetroItem::random);
        } else active = next;

        active -> setGridPos(start_x_pos, 0, true);
        active -> setFlag(QGraphicsItem::ItemIsFocusable, true);
        active -> setFocus();
        figures_text -> setText(QString::number(++figures));

        next = generateItem();
        next -> rotate(TetroItem::random);
        next -> setGridPos(info_offset_x, 1);
        addItem(next);

        if (checkCollision()) {
            ended = true;
            emit gameOver();
        }
    }

    void moveItem() {
        active -> pushDown();
        if (checkCollision()) {
            pauseTimer();
            active -> pushUp();

            QHash<int, int> rows;
            {
                QList<QGraphicsItem *> children = active -> childItems();

                for(QList<QGraphicsItem *>::Iterator ch = children.begin(); ch != children.end(); ch++) {
                    TetroPart * part = ((TetroPart *)*ch);
                    QPointF point = part -> gridPos();
                    places[point.y()].first[point.x()] = part;
                    if (++places[point.y()].second == end_x_pos)
                        rows.insert(point.y(), 1);
                    part -> setParentItem(0);
                    part -> setGridPos(point.toPoint());
                }
            }

            delete active;
            active = 0;
            if (!rows.isEmpty())
                removeRows(rows);
            startTimer();
        }
    }

    bool checkCollision(bool can_move = false) {
        QList<QGraphicsItem *> children = active -> childItems();
        for(QList<QGraphicsItem *>::Iterator ch = children.begin(); ch != children.end(); ch++) {
            QPoint point = ((TetroPart *)*ch) -> gridPos().toPoint();
            QPoint correction;

            if (point.x() < 0) {
                if (can_move)
                    correction.setX(-point.x());
                else return true;
            }

            if (point.x() >= end_x_pos) {
                if (can_move)
                    correction.setX((point.x() - 1 - end_x_pos));
                else return true;
            }

            if (point.y() < 0) {
                if (can_move)
                    correction.setY(-point.y());
                else return true;
            }

            if (point.y() >= end_y_pos) return true;

            if (places[point.y() + correction.y()].first[point.x() + correction.x()])
                return true;

            active -> setPos(active -> pos() + correction * GRANULARITY) ;
        }

        return false;
    }

    void removeRows(const QHash<int, int> & rows) {
        int max = -999999;

        for(QHash<int, int>::ConstIterator y = rows.cbegin(); y != rows.cend(); y++) {
            qDeleteAll(places[y.key()].first);
            places[y.key()] = QPair<QVector<TetroPart *>, int>(QVector<TetroPart *>().fill(0, end_y_pos), 0);
            max = qMax(max, y.key());
        }

        int step = 0;
        for(int y = max; y > -1; y--) {
            if (rows.contains(y))
                step += rows[y];
            else {
                QVector<TetroPart *> parts = places[y].first;
                for(QVector<TetroPart *>::Iterator part = parts.begin(); part != parts.end(); part++)
                    if ((*part))
                        (*part) -> iterateGridPos(QPoint(0, step));
                places.swap(y, y + step);
            }
        }
        lines_text -> setText(QString::number(lines += step));
        score_text -> setText(QString::number(scores += level * (step * LINE_POINTS + (step - 1 * LINE_POINTS))));
        level_text -> setText(QString::number(level = (lines / 20) + 1));

        if (level >= 9)
            emit congratulations();
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
                return new RectItem();
        }
    }
public:
    TetroScene(int width, int height, QObject * parent = 0) : QGraphicsScene(parent), active(0), next(0),
        level_text(0), score_text(0), lines_text(0), figures_text(0), rotateAnimation(0),
        field_width(width), field_height(height), level(1), scores(0), lines(0), figures(0), ended(false)
    {
        setBackgroundBrush(QBrush(BCOLOR));
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));

        setSceneRect(0, 0, width, height);
        end_x_pos = width / GRANULARITY;
        start_x_pos = end_x_pos / 2;
        end_y_pos = height / GRANULARITY;
        info_offset_x = end_x_pos + 3;

        fillMatrix();
    }

    void reset() {
        clear();
        if (rotateAnimation) rotateAnimation -> stop();
        rotateAnimation = 0;
        int base_top = 8;

        level = 1;
        scores = 0;
        lines = 0;
        figures = 0;
        QFont f = font();
        f.setBold(true);
        f.setPixelSize(16);

        level_text = new TextItem(QStringLiteral("Level: "), QString::number(level));
        level_text -> setFont(f);
        level_text -> setPos(info_offset_x * GRANULARITY, base_top++ * GRANULARITY);
        addItem(level_text);

        score_text  = new TextItem(QStringLiteral("Score: "), QString::number(scores));
        score_text -> setFont(f);
        score_text -> setPos(info_offset_x * GRANULARITY, base_top++ * GRANULARITY);
        addItem(score_text);

        lines_text  = new TextItem(QStringLiteral("Lines: "), QString::number(lines));
        lines_text -> setFont(f);
        lines_text -> setPos(info_offset_x * GRANULARITY, base_top++ * GRANULARITY);
        addItem(lines_text);

        figures_text  = new TextItem(QStringLiteral("Figures: "), QString::number(figures));
        figures_text -> setFont(f);
        figures_text -> setPos(info_offset_x * GRANULARITY, base_top++ * GRANULARITY);
        addItem(figures_text);

        active = 0;
        next = 0;
        ended = false;
        fillMatrix();
    }

    void startTimer() {
        qsrand(QDateTime::currentMSecsSinceEpoch() / 8);
        timer -> start(DEFAULT_SPEED + (1 - level) * LEVEL_SPEED);
        onTimer();
    }

    void pauseTimer() {
        timer -> stop();
    }

    void buildAnimationScreen(const QPoint & center) {
        int limit = 7, xShift = 100, yShift = 100;
        int scale = qMin(center.x(), center.y()) * 0.7;
        float angleUnit = 6.28 / limit;

        RotationContainer * container = new RotationContainer();

        for(int i = 0; i < limit; i++) {
            TetroItem * item = generateItem((ItemTypes)i);
            item -> setParentItem(container);
            item -> setPos(
                cos(angleUnit * i) * scale + xShift,
                sin(angleUnit * i) * scale + yShift
            );
        }

        container -> setPos(container -> childrenBoundingRect().translated(0, 0).center() / 2 - QPoint(90, 0));
        container -> setTransformOriginPoint(container -> childrenBoundingRect().center());
        addItem(container);

        rotateAnimation = new QPropertyAnimation(container, "rotation");
        rotateAnimation -> setDuration(24000);
        rotateAnimation -> setEasingCurve(QEasingCurve::Linear);
        rotateAnimation -> setStartValue(0);
        rotateAnimation -> setEndValue(360);
        rotateAnimation -> setLoopCount(-1);
        rotateAnimation -> start(QAbstractAnimation::DeleteWhenStopped);
    }
};

#endif // TETRO_SCENE

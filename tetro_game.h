#ifndef TETRO_GAME
#define TETRO_GAME

#include <qgraphicsview.h>
#include <qlabel.h>
#include <qpushbutton.h>
//#include <QOpenGLWidget>

#include "tetro_scene.h"

#define SCREEN_WIDTH 9 * GRANULARITY + 1
#define SCREEN_HEIGHT 16 * GRANULARITY + 1

#define MENU_SIZE 300
#define START_BTN_SIZE 100

class TetroGame : public QGraphicsView {
    Q_OBJECT

    TetroScene * scene;
    QPushButton * startBtn;
protected:
    void buildMenu() {
        QPoint center = QPoint(parentWidget() -> width() / 2, parentWidget() -> height() / 2);
        startBtn -> setGeometry(center.x() - START_BTN_SIZE / 2, center.y() - START_BTN_SIZE / 2, START_BTN_SIZE, START_BTN_SIZE);

        QPropertyAnimation * animation = new QPropertyAnimation(startBtn, "geometry");
        animation -> setDuration(1000);
        animation -> setEasingCurve(QEasingCurve::Linear);
        animation -> setStartValue(QRectF(center.x(), center.y(), 0, 0));
        animation -> setEndValue(QRectF(center.x() - START_BTN_SIZE / 2, center.y() - START_BTN_SIZE / 2, START_BTN_SIZE, START_BTN_SIZE));
        animation -> start(QAbstractAnimation::DeleteWhenStopped);

        scene -> buildAnimationScreen(center);
    }
public slots:
    void start() {
        QPoint center = QPoint(parentWidget() -> width() / 2, parentWidget() -> height() / 2);
        QPropertyAnimation * animation = new QPropertyAnimation(startBtn, "geometry");
        animation -> setDuration(500);
        animation -> setEasingCurve(QEasingCurve::Linear);
        animation -> setEndValue(QRectF(center.x(), center.y(), 0, 0));
        animation -> start(QAbstractAnimation::DeleteWhenStopped);

        scene -> reset();
        scene -> startTimer();
    }

    void pause() { scene -> pauseTimer(); }
    void resume() { scene -> startTimer(); }

    void paused() {

    }
    void resumed() {

    }

    void showStartScreen() {
        buildMenu();
    }

    void showGameOver() {
        pause();
        QLabel * label = new QLabel(QStringLiteral("Game is over :("));
        QFont f = label -> font();
        f.setPixelSize(32);
        label -> setFont(f);
        scene -> addWidget(label);
    }
public:
    TetroGame(QWidget * parent = 0) : QGraphicsView(parent), startBtn(0) {
        setStyleSheet("border: transparent;");
//        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//        setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);

//        QOpenGLWidget * myWidget = new QOpenGLWidget(this);
//        setViewport(myWidget);
//        myWidget -> makeCurrent();

        scene = new TetroScene(SCREEN_WIDTH, SCREEN_HEIGHT, this);
        setScene(scene);
        setRenderHint(QPainter::Antialiasing);
        setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
        connect(scene, SIGNAL(gameOver()), this, SLOT(showGameOver()));
        connect(scene, SIGNAL(paused()), this, SLOT(paused()));
        connect(scene, SIGNAL(resumed()), this, SLOT(resumed()));

        startBtn = new QPushButton(QStringLiteral("Start"), this);
        startBtn -> setGeometry(0,0,0,0);
        startBtn -> setStyleSheet(QStringLiteral("border-radius: 6px; background-color: #EEE; border: 2px solid #ff0000"));
        connect(startBtn, SIGNAL(clicked(bool)), this, SLOT(start()));

        buildMenu();
    }

    ~TetroGame() { pause(); }
};

#endif // TETRO_GAME

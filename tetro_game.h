#ifndef TETRO_GAME
#define TETRO_GAME

#include <qgraphicsview.h>
#include <qlabel.h>
//#include <QOpenGLWidget>

#include "tetro_scene.h"

#define SCREEN_WIDTH 9 * GRANULARITY + 1
#define SCREEN_HEIGHT 16 * GRANULARITY + 1

class TetroGame : public QGraphicsView {
    Q_OBJECT

    TetroScene * scene;
    QWidget * menu;
public slots:
    void start() {
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
    TetroGame(QWidget * parent = 0) : QGraphicsView(parent) {
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
        connect(scene, SIGNAL(gameOver()), this, SLOT(showGameOver()));
        connect(scene, SIGNAL(paused()), this, SLOT(paused()));
        connect(scene, SIGNAL(resumed()), this, SLOT(resumed()));
    }

    ~TetroGame() { pause(); }
};

#endif // TETRO_GAME

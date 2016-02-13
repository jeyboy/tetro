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
public slots:
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
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);

//        QOpenGLWidget * myWidget = new QOpenGLWidget(this);
//        setViewport(myWidget);
//        myWidget -> makeCurrent();

        scene = new TetroScene(SCREEN_WIDTH, SCREEN_HEIGHT, this);
        setScene(scene);
        connect(scene, SIGNAL(gameOver()), this, SLOT(showGameOver()));
    }

    ~TetroGame() { pause(); }

    void showStartScreen() {

    }

    void start() { scene -> startTimer(); }
    void pause() { scene -> pauseTimer(); }
};

#endif // TETRO_GAME

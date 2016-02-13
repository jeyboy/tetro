#ifndef TETRO_GAME
#define TETRO_GAME

#include <qgraphicsview.h>
//#include <QOpenGLWidget>

#include "tetro_scene.h"

#define SCREEN_WIDTH 9 * GRANULARITY + 1
#define SCREEN_HEIGHT 16 * GRANULARITY + 1

class TetroGame : public QGraphicsView {
    Q_OBJECT

    TetroScene * scene;
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
    }

    ~TetroGame() { pause(); }

    void start() { scene -> startTimer(); }
    void pause() { scene -> pauseTimer(); }
};

#endif // TETRO_GAME

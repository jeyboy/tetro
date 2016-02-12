#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tetro_game.h"

#include <qmainwindow.h>

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow {
    Q_OBJECT

    Ui::MainWindow * ui;
    TetroGame * game;
public:
    explicit MainWindow(QWidget * parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H

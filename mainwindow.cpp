#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui -> setupUi(this);
    game = new TetroGame(this);
    setCentralWidget(game);

    game -> showStartScreen();
}

MainWindow::~MainWindow() {
    delete ui;
}

//void MainWindow::updateButtonsGeometry() {
//    int buttonCount = buttonList.size();
//    float angleUnit = 6.28 / buttonCount;

//    for(int i = 0; i < buttonCount; i++) {
//        QPushButton * btn = buttonList.at(i);
//        QPropertyAnimation * animation = new QPropertyAnimation(btn, "geometry");
//        animation -> setDuration(1000);
//        animation -> setEasingCurve(QEasingCurve::Linear);
//        animation -> setEndValue(
//            QRectF(
//                cos(angleUnit * i) * scale + xShift,
//                sin(angleUnit * i) * scale + yShift,
//                buttonSize,
//                buttonSize
//            )
//        );
//        animation -> start(QAbstractAnimation::DeleteWhenStopped);
//    }
//}

//void MainWindow::on_addButton_clicked() {
//    QPushButton * btn = new QPushButton(this);
//    btn -> setText(QString::number(buttonList.size() + 1));
//    btn -> setGeometry(ui -> addButton -> geometry());
//    btn -> show();
//    buttonList.append(btn);
//    updateButtonsGeometry();
//}

//void MainWindow::on_removeButton_clicked() {
//    if (buttonList.isEmpty()) return;

//    buttonList.takeLast() -> deleteLater();
//    updateButtonsGeometry();
//}

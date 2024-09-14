#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {

    gameBase = new GameBase(this);
    setCentralWidget(gameBase);
}

MainWindow::~MainWindow() {}

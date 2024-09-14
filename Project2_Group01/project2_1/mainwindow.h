#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamebase.h" // 包含GameBase类的头文件

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    GameBase *gameBase; // GameBase对象
};

#endif // MAINWINDOW_H


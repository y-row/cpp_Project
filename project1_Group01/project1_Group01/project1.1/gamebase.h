#ifndef GAMEBASE_H
#define GAMEBASE_H

#include <QGraphicsView>
#include <QMediaPlayer>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QPixmap>
#include <QString>
#include <QSound>
#include <QLabel>
#include <QPropertyAnimation>
#include <QtWidgets>
#include <QMouseEvent>
#include <QGraphicsScene>
#include "mario.h"
#include "floor.h"
#include "waterpipe.h"   //綠色水管
#include "normalbrick.h" //普通磚
#include "stonebrick.h"  //石磚
#include "brokenbrick.h"
#include "boxbrick.h"
#include "super_mushroom.h"
#include "fire_flower.h"
#include "coin.h"
#include "flag.h"
#include "toxic_mushroom.h"
#include "flag_pole.h"
#include "bullet.h"
#include "superstar.h"
#include "turtle.h"
#include "flower.h"

class GameBase : public QGraphicsView {
    Q_OBJECT
public:
    GameBase(QWidget *parent = nullptr);

public slots:
    void gameStart();
    void updateGame(); //更新遊戲frame
    void switchToUndergroundScene(); // 切換到地下場景的方法


protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
private:
    void generateCoinMap();
    void gameWin();
    QTableWidget scoreBoard;
    QPixmap img; // 圖片對象
    QGraphicsScene *background; // 背景場景
    QGraphicsScene *undergroundScene; // 地下場景
    QPushButton *button_start; // 開始按鈕
    QPushButton *button_exit; // 退出按鈕
    Floor *floor; // 地板對象
    WaterPipe *pipe; // 水管
    NormalBrick *normalbrick; // 普通磚
    StoneBrick *stonebrick;   //石磚
    BrokenBrick *brokenbrick;
    BoxBrick *boxbrick;
    QLabel *lifeLabel; //生命值顯示
    QLabel *coinLabel; //金錢數顯示
    QLabel *mousePosLabel;
    QLabel *scoreLabel; // 結束出現的score label

    Super_mushroom *supermushroom;
    Fire_flower *fireflower;
    Coin *coin;
    Flag *flag;
    Flag_pole *flagpole;
    Toxic_mushroom *toxicmushroom;
    Bullet *bullet;
    SuperStar *superstar;
    Turtle *turtle;
    Flower *flower;
    QTimer *gameTimer,*undergroundTimer; //遊戲計時

    QPropertyAnimation *animation;
    QPointF endPos;

    MediaPlayer *mediaPlayer;
    Mario *mario;
    bool isUnderGround;

};

#endif // GAMEBASE_H

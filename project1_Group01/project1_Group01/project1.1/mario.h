#ifndef MARIO_H
#define MARIO_H

#include <QGraphicsObject>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include "superstar.h"
#include "mediaplayer.h"

enum action{stand,run1,run2,jump1,jump2,block,die};//站、跑、跳、被撞到、死掉
enum direction{R,L};                               //向左或向右
enum state{alive,dead,invincible,complete,movingdown};        //馬力歐狀態
class Mario : public QGraphicsObject
{
    Q_OBJECT
public:
    Mario(int x, int y);
    static int num_coin;
    static int hp;
    static bool isBig;         //檢查是否為大
    static int num_bullet;     //子彈的數量
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    //void setPos(int x, int y);
    int moveMario(); //移動馬力歐
    float getX();
    float getY();
    void setcanfire(bool);
    bool getcanfire();
    void setnum_bullet(int a);
    void marioGoDie();
    int getnum_bullet();
    int gethp();
    int getCoinNumber();//錢幣的數量
    void getCoin();//獲得錢幣的函數
    int actionType[2]; //0:動作 1:方向
    void changeImage(); //轉換馬力歐圖片
    void touchtoxic();
    void touchsuper();
    qreal getverticalSpeed();
    bool getstar();
    bool getCanJump();
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

private:
    QPixmap marioPixmap;
    int moveSpeed;
    float posX;
    float posY;
    /*移動相關參數*/
    qreal gravity;       // 重力加速度
    qreal jumpSpeed;
    qreal verticalSpeed; // 垂直速度
    qreal currentJumpHeight;
    qreal initialYPos;

    void setSpeed(int x);
    void setverticalSpeed(int x);
    void setgravity(int x);
    void setjumpSpeed(int x);
    QRectF collisionRect() const; // 碰撞矩形函式

    // 移動方向的標誌
    bool isMovingUp;    //測試用，垂直往上走
    bool isMovingDown;
    bool isMovingLeft;
    bool isMovingRight;
    bool canMoveRight;
    bool canMoveLeft;
    bool isJumping;     //跳躍
    bool canJump;       //檢查是否已經站在地板上，如果是才可以再跳躍

    bool canfire;       //檢查是否可以射出bullet

    QGraphicsItem *collidingItem; // 保存與Mario碰撞的物件指標
    int timerID;
    int time;   //mario碰到toxic mushroom的間隔時間
    int time2;  //mario碰到super star後的無敵時間
    bool star;  //是否有拿到super star
    MediaPlayer *mediaPlayer; //音樂
};

#endif // MARIO_H

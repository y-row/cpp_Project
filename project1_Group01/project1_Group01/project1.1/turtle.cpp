#include "turtle.h"
#include <QDebug>
#include <QGraphicsScene>
#include <iostream>
Turtle::Turtle(int x, int y) : posX(x), posY(y) {
    vx = 3;
    vy = 5;
    g = 2;
    TurtlePixmap.load(":/new/prefix1/image/Rtortoise1.png");    //turtle: 60*74  shell: 50*50
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Turtle::move);  // 連接信號與槽
    timer->start(30);
    time1 = 0;
    time2 = 0;
    timerID = startTimer(50);  // 0.05 sec clock
    shell = false;
    spin = false;
}

void Turtle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(posX, posY, TurtlePixmap);
}

QRectF Turtle::boundingRect() const {
    return QRectF(posX, posY, TurtlePixmap.width(), TurtlePixmap.height());
}

void Turtle::setPosition(qreal x, qreal y) {
    posX = x;
    posY = y;
    setPos(posX, posY);
}

QRectF Turtle::collisionRect() const {
    return boundingRect().adjusted(-1, -1, -1, -1); // 小調整增加碰撞範圍
}

qreal Turtle::getY() const {
    return posY;
}

qreal Turtle::getX() const {
    return posX;
}

void Turtle::timerEvent(QTimerEvent *event){
    if(event -> timerId() == timerID and timerID != 0){
        time1++;
        if(time2 == 0){
            time2 = 0;
            if(!spin){
                shell = false;
            }
        }
        else{
            time2--;
        }
    }
}

void Turtle::move(){
    vy += g;
    //移動
    posX += vx;
    posY += vy;
    update();

    QList<QGraphicsItem*> collidingList = collidingItems(Qt::IntersectsItemBoundingRect);

    for (QGraphicsItem* item : collidingList) {
        // 檢查碰撞地板
        Floor* currentFloor = dynamic_cast<Floor*>(item);
        if (currentFloor) {
            posY = currentFloor -> getY() - TurtlePixmap.height();
            vy = 0;
        }

        //踩在Normal Brick & Stone Brick上
        NormalBrick* currentBrick= dynamic_cast<NormalBrick*>(item);
        StoneBrick* stoneBrick= dynamic_cast<StoneBrick*>(item);
        if (currentBrick||stoneBrick){
            if(vy > 6){    //落到磚塊上
                posY = (currentBrick)?currentBrick->getY():stoneBrick->getY() - TurtlePixmap.height();
                vy = 0;
           }
           else{   //此時在地板上
                vx *= -1;
                return;
           }
       }

        //碰到水管反彈
        WaterPipe* waterpipe= dynamic_cast<WaterPipe*>(item);
        if (waterpipe) {
            if(vy < 6){ //此時在地板上
                vx *= -1;
            }
            else{ //落到水管上
                posY = waterpipe -> getY() - TurtlePixmap.height();
                vy = 0;
            }
        }

        //踩在Box Brick & Broken Brick上
        BoxBrick *boxbrick = dynamic_cast<BoxBrick*>(item);
        BrokenBrick* brokenBrick = dynamic_cast<BrokenBrick*>(item);
        if(boxbrick or brokenBrick){
            posY = (boxbrick)?boxbrick->getY():brokenBrick->getY() - TurtlePixmap.height();
            vy = 0;
        }

       //碰到子彈消失
       Bullet *bullet = dynamic_cast<Bullet*>(item);
       if(bullet){
           delete bullet;
           delete this;
       }
       Toxic_mushroom *toxicmushroom = dynamic_cast<Toxic_mushroom*>(item);
       if(toxicmushroom&&shell){
           if(!toxicmushroom->disappear0){
               toxicmushroom->disappear();
           }

           continue;
    }

        Mario *mario = dynamic_cast<Mario*>(item);
        if(mario){
            if(mario->getstar()){
                delete this;
            }
            else if(mario -> getverticalSpeed() > 0) {
                shell = true;
                if(time2 == 0){
                    time2 = 60; //計時3秒
                    TurtlePixmap.load(":/new/prefix1/image/shell1.png");
                }
                if(time2 > 0 and time2 < 50 and shell){ //踩第2次
                    spin = true;
                }
            }
            else if(spin||!shell){
                    mario -> touchtoxic();
            }
        }
    }

    //移動的動畫
    if(!shell){ //每0.4秒動一次直到變換型態
        if(vx > 0){
            if(time1 % 16 > 0 and time1 % 16 < 8){  //0 ~ 0.2秒
                TurtlePixmap.load(":/new/prefix1/image/Rtortoise1.png");
            }
            else
                TurtlePixmap.load(":/new/prefix1/image/Rtortoise2.png");
        }
        else{
            if(time1 % 16 > 8){//0.2 ~ 0.4秒
                TurtlePixmap.load(":/new/prefix1/image/Ltortoise1.png");
            }
            else
                TurtlePixmap.load(":/new/prefix1/image/Ltortoise2.png");
        }
    }
    else if(spin){ //每0.2秒自轉1圈 & 水平速度增加5倍
        if(vx > 0){
            vx = 13;
        }
        else
            vx = -13;
        int a = time1 % 4;
        switch(a){
        case 0:
            TurtlePixmap.load(":/new/prefix1/image/shell1.png");
            break;
        case 1:
            TurtlePixmap.load(":/new/prefix1/image/shell2.png");
            break;
        case 2:
            TurtlePixmap.load(":/new/prefix1/image/shell3.png");
            break;
        case 3:
            TurtlePixmap.load(":/new/prefix1/image/shell4.png");
            break;
        }
    }
}


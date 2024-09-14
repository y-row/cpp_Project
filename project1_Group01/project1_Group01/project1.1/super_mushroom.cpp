#include "super_mushroom.h"
#include "waterpipe.h"

Super_mushroom::Super_mushroom(int x, int y) : posX(x), posY(y)
{
    vx = 3;
    vy = 5;
    g = 2;
    mushroomPixmap.load(":/new/prefix1/image/item/super mushroom.png");
    mushroomPixmap.scaled(50,50);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Super_mushroom::move);  // 連接信號與槽
    timer->start(20);
}

void Super_mushroom:: paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(posX, posY, mushroomPixmap);
}

QRectF Super_mushroom::boundingRect() const {
    return QRectF(posX, posY, mushroomPixmap.width(), mushroomPixmap.height());
}

void Super_mushroom::setPosition(qreal x, qreal y)
{
    posX = x;
    posY = y;
    setPos(posX, posY);
}

void Super_mushroom::move(){
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
            posY = currentFloor -> getY() - mushroomPixmap.height();
            vy = 0;
        }

        //踩在Brick上
        NormalBrick* currentBrick= dynamic_cast<NormalBrick*>(item);
        StoneBrick* stoneBrick= dynamic_cast<StoneBrick*>(item);
        BrokenBrick* brokenbrick=dynamic_cast<BrokenBrick*>(item);
        if (currentBrick||stoneBrick||brokenbrick){
            if(posY < 460){    //落到磚塊上
                posY = (currentBrick) ? (currentBrick->getY()- mushroomPixmap.height())
                                      :(stoneBrick)?( stoneBrick->getY() - mushroomPixmap.height())
                                      :(brokenbrick->getY()- mushroomPixmap.height());
                vy = 0;
           }
           else{   //此時在地板上
                vx *= -1;
           }
       }

        //碰到水管反彈
        WaterPipe* waterpipe= dynamic_cast<WaterPipe*>(item);
        if (waterpipe) {
            if(vy < 6){ //此時在地板上
                vx *= -1;
            }
            else{ //落到水管上
                posY = waterpipe -> getY() - mushroomPixmap.height();
                vy = 0;
            }
        }

        //踩在Box Brick & Broken Brick上
        BoxBrick *boxbrick = dynamic_cast<BoxBrick*>(item);
        BrokenBrick* brokenBrick = dynamic_cast<BrokenBrick*>(item);
        if(boxbrick or brokenBrick){
            posY = ((boxbrick)?boxbrick->getY():brokenBrick->getY()) - mushroomPixmap.height();
            vy = 0;
        }

        Mario *mario = dynamic_cast<Mario*>(item);
        if(mario){
            mario -> touchsuper();
            delete this;
        }
    }
}

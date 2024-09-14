#include "toxic_mushroom.h"

Toxic_mushroom::Toxic_mushroom(int x, int y) : posX(x), posY(y)
{
    vx = 3;
    vy = 0;
    g = 2;
    toxicmushroomPixmap.load(":/new/prefix1/image/toxic mushroom1.png");
    toxicmushroomPixmap.scaled(50,50);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Toxic_mushroom::move);  // 連接信號與槽
    timer->start(30);
    time1 = 0;
    time2 = 0;
    timerID = startTimer(500);  // 0.5 sec clock
    disappear0 = false;
}

void Toxic_mushroom::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(posX, posY, toxicmushroomPixmap);
}

QRectF Toxic_mushroom::boundingRect() const {
    return QRectF(posX, posY, toxicmushroomPixmap.width(), toxicmushroomPixmap.height());
}

void Toxic_mushroom::setPosition(qreal x, qreal y) {
    posX = x;
    posY = y;
    setPos(posX, posY);
}

void Toxic_mushroom::move(){
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
            posY = currentFloor -> getY() - toxicmushroomPixmap.height();
            vy = 0;
            continue;
        }

        //踩在Normal Brick & Stone Brick上
        NormalBrick* currentBrick= dynamic_cast<NormalBrick*>(item);
        StoneBrick* stoneBrick= dynamic_cast<StoneBrick*>(item);
        if (currentBrick||stoneBrick){
            if(posY < 460){    //落到磚塊上
                posY = (currentBrick)?currentBrick->getY():stoneBrick->getY() - toxicmushroomPixmap.height();
                vy = 0;
           }
           else{   //此時在地板上
                vx *= -1;
                continue;
           }
       }

        //碰到水管反彈
        WaterPipe* waterpipe= dynamic_cast<WaterPipe*>(item);
        if (waterpipe) {
            if(vy < 6){ //此時在地板上
                vx *= -1;
            }
            else{ //落到水管上
                posY = waterpipe -> getY() - toxicmushroomPixmap.height();
                vy = 0;
            }
            continue;
        }

        //踩在Box Brick & Broken Brick上
        BoxBrick *boxbrick = dynamic_cast<BoxBrick*>(item);
        BrokenBrick* brokenBrick = dynamic_cast<BrokenBrick*>(item);
        if(boxbrick or brokenBrick){
            posY = (boxbrick)?boxbrick->getY():brokenBrick->getY() - toxicmushroomPixmap.height();
            vy = 0;
            continue;
        }

        //碰到子彈消失、碰到旋轉龜龜消失
        Bullet *bullet = dynamic_cast<Bullet*>(item);
        if(bullet){
            delete bullet;
            delete this;
        }
        Turtle *ctturrtle= dynamic_cast<Turtle*>(item);
        if(ctturrtle){
            if(ctturrtle->shell){
                disappear();
            }
        }
        Mario *mario = dynamic_cast<Mario*>(item);
        if(mario){
            if(mario -> getverticalSpeed() > 7 or mario -> getstar()){
                disappear();
            }
            else{
                if(!disappear0){
                mario -> touchtoxic();
                }
            }
            continue;
        }
    }

       //時間到了就消失
       if(disappear0 and time1 == 0){
           delete this;
       }


    //移動的動畫 每0.5秒動一次直到死亡
    if(!disappear0){
        if(time2 % 2 == 1){
            toxicmushroomPixmap.load(":/new/prefix1/image/toxic mushroom1.png");
        }
        else
            toxicmushroomPixmap.load(":/new/prefix1/image/toxic mushroom2.png");
    }
}

void Toxic_mushroom::timerEvent(QTimerEvent *event){
    if(event -> timerId() == timerID and timerID != 0){
        time1 = (time1 == 0)? 0 : time1 - 1;
        time2++;
    }
}

void Toxic_mushroom::disappear(){
    vx = 0;
    toxicmushroomPixmap.load(":/new/prefix1/image/toxic mushroom3.png");
    time1 = 1;
    disappear0 = true;
}

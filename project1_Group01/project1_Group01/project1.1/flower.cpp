#include "flower.h"

Flower::Flower(int x, int y) : posX(x), posY(y) {
    alive=true;
    FlowerPixmap.load(":/new/prefix1/image/flower1.6.png");//6: 60*66  4: 60*96  2: 60*126
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Flower::move);  // 連接信號與槽
    timer->start(30);
    time1 = 0;
    timerID = startTimer(200);  // 0.2 sec clock
    vy = 2;
}

void Flower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(posX, posY, FlowerPixmap);
}

QRectF Flower::boundingRect() const {
    return QRectF(posX, posY, FlowerPixmap.width(), FlowerPixmap.height());
}

void Flower::setPosition(qreal x, qreal y) {
    posX = x;
    posY = y;
    setPos(posX, posY);
}

QRectF Flower::collisionRect() const {
    return boundingRect().adjusted(5, 5, -5, -5); // 小調整增加碰撞範圍
}

qreal Flower::getY() const {
    return posY;
}

qreal Flower::getX() const {
    return posX;
}

void Flower::timerEvent(QTimerEvent *event){
    if(event -> timerId() == timerID and timerID != 0){
        if(time1 == 40){    //8秒為1週期
            time1 = 0;
        }
        else
            time1++;
    }
}

void Flower::move(){

    //碰到mario
    Mario *currentmario;
    QList<QGraphicsItem*> collidingmarioList = collidingItems(Qt::IntersectsItemBoundingRect);
    for (QGraphicsItem* item : collidingmarioList) {
        currentmario = dynamic_cast<Mario*>(item);
        if (currentmario and time1 <= 23) { //只有flower顯示時對mario才有傷害
            if(currentmario->getstar()){
                delete this;
            }
            currentmario -> touchtoxic();   //馬力歐碰到的效果和碰到毒蘑菇一樣
            continue;
        }
    }

    //動畫
    if(time1 >= 0 and time1 <= 5){ //0 ~ 1.2秒
        this->setVisible(true);
        int a = time1 % 6;
        posY -= vy;
        update();
        switch(a){
        case 0:
            FlowerPixmap.load(":/new/prefix1/image/flower1.6.png");
            break;
        case 1:
            FlowerPixmap.load(":/new/prefix1/image/flower1.5.png");
            break;
        case 2:
            FlowerPixmap.load(":/new/prefix1/image/flower1.4.png");
            break;
        case 3:
            FlowerPixmap.load(":/new/prefix1/image/flower1.3.png");
            break;
        case 4:
            FlowerPixmap.load(":/new/prefix1/image/flower1.2.png");
            break;
        case 5:
            FlowerPixmap.load(":/new/prefix1/image/flower1.1.png");
            break;
        }
    }

    if(time1 >= 6 and time1 <= 17){ //1.2 ~ 3.6秒
        int a = time1 % 2;
        if(a == 0){
            FlowerPixmap.load(":/new/prefix1/image/flower1.2.png");
        }
        else
            FlowerPixmap.load(":/new/prefix1/image/flower1.1.png");
    }

    if(time1 >= 18 and time1 <= 23){    //3.6 ~ 4.8秒
        posY += vy;
        int a = time1 % 6;
        switch(a){
        case 0:
            FlowerPixmap.load(":/new/prefix1/image/flower1.2.png");
            break;
        case 1:
            FlowerPixmap.load(":/new/prefix1/image/flower1.1.png");
            break;
        case 2:
            FlowerPixmap.load(":/new/prefix1/image/flower1.4.png");
            break;
        case 3:
            FlowerPixmap.load(":/new/prefix1/image/flower1.3.png");
            break;
        case 4:
            FlowerPixmap.load(":/new/prefix1/image/flower1.6.png");
            break;
        case 5:
            FlowerPixmap.load(":/new/prefix1/image/flower1.5.png");
            break;
        }
    }

    if(time1 >= 24 and time1 <= 40){    //4.8 ~ 8秒
        this->setVisible(false);
    }
}


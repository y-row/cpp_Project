#include "normalbrick.h"

NormalBrick::NormalBrick(int x, int y) {
    posX=x;
    posY=y;
    coin=0;
    canGetCoin=false;
    NorbricPixmap.load(":/new/prefix1/image/brick/normal brick.png");
    NorbricPixmap.scaled(50,50);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &NormalBrick::setCanGetCoin);
}

void NormalBrick::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(posX, posY, NorbricPixmap);
}

QRectF NormalBrick::boundingRect() const {
    return QRectF(posX, posY, 50, 50);
}

void NormalBrick::setPosition(qreal x, qreal y) {
    posX = x;
    posY = y;
    setPos(posX, posY);
}

qreal NormalBrick::getY() const {
    return posY;
}

qreal NormalBrick::getX() const {
    return posX;
}

void NormalBrick::setNumCoin(int x){
    this->coin=x;
    canGetCoin=true;
}

int NormalBrick::getNumCoin(){
   return coin;
}

bool NormalBrick::getCoin(){
    if(canGetCoin){
        canGetCoin=false;
        coin--;
        if(coin<=0){
          return true; //要砍掉
        }
        timer->start(400);
    }
    //不能拿到coin自然不用砍掉
    return false;
}

void NormalBrick::setCanGetCoin(){
    canGetCoin=true;
    timer->stop();
}
//QRectF NormalBrick::collisionRect() const {
//    return boundingRect().adjusted(5, 5, -5, -5); // 小調整增加碰撞範圍
//}

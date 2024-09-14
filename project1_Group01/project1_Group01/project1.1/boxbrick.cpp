#include "boxbrick.h"
int BoxBrick::totalBoxBrick=0;
BoxBrick* BoxBrick::boxBrickList[15]={nullptr};
BoxBrick::BoxBrick(int x, int y) : ID(totalBoxBrick),posX(x), posY(y) {
    //ID=boxBrickNumber;//第幾號出生
    totalBoxBrick++;
    boxBrickList[ID]=this;
   BoxbricPixmap.load(":/new/prefix1/image/brick/box brick.png");
   BoxbricPixmap= BoxbricPixmap.scaled(50,50);
}

void BoxBrick::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(posX, posY, BoxbricPixmap);
}

QRectF BoxBrick::boundingRect() const {
    return QRectF(posX, posY, BoxbricPixmap.width(), BoxbricPixmap.height());
}

void BoxBrick::setPosition(qreal x, qreal y) {
    posX = x;
    posY = y;
    setPos(posX, posY);
}

QRectF BoxBrick::collisionRect() const {
    return boundingRect().adjusted(5, 5, -5, -5); // 小調整增加碰撞範圍
}

qreal BoxBrick::getY() const {
    return posY;
}


qreal BoxBrick::getX() const {
    return posX;
}

BoxBrick::~BoxBrick() {
    boxBrickList[ID]=nullptr;
}

#include "brokenbrick.h"

BrokenBrick::BrokenBrick(int x, int y) : posX(x), posY(y) {
    BrobricPixmap.load(":/new/prefix1/image/brick/broken brick.png");
    BrobricPixmap=BrobricPixmap.scaled(50,50);
}

void BrokenBrick::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(posX, posY, BrobricPixmap);
}

QRectF BrokenBrick::boundingRect() const {
    return QRectF(posX, posY, BrobricPixmap.width(), BrobricPixmap.height());
}

void BrokenBrick::setPosition(qreal x, qreal y) {
    posX = x;
    posY = y;
    setPos(posX, posY);
}

QRectF BrokenBrick::collisionRect() const {
    return boundingRect().adjusted(5, 5, -5, -5); // 小調整增加碰撞範圍
}

qreal BrokenBrick::getY() const {
    return posY;
}

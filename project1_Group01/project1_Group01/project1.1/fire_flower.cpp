#include "fire_flower.h"

Fire_flower::Fire_flower(int x, int y) : posX(x), posY(y)
{
    fireflowerPixmap.load(":/new/prefix1/image/item/Fire Flower.png");
    fireflowerPixmap=fireflowerPixmap.scaled(50,50);
}

void Fire_flower::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(posX, posY, fireflowerPixmap);
}

QRectF Fire_flower::boundingRect() const {
    return QRectF(posX, posY, fireflowerPixmap.width(), fireflowerPixmap.height());
}

void Fire_flower::setPosition(qreal x, qreal y) {
    posX = x;
    posY = y;
    setPos(posX, posY);
}

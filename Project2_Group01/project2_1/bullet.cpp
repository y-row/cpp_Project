#include "bullet.h"

Bullet::Bullet(qreal x, qreal y) : posX(x), posY(y)
{
    bulletPixmap.load(":/new/prefix1/dataset/bullet.png");
    bulletPixmap=bulletPixmap.scaled(20,20);
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(posX, posY, bulletPixmap);
}

QRectF Bullet::boundingRect() const {
    return QRectF(posX, posY, bulletPixmap.width(), bulletPixmap.height());
}

void Bullet::setPosition(qreal x, qreal y) {
    posX = x;
    posY = y;
    setPos(posX, posY);
}

#include "stonebrick.h"

StoneBrick::StoneBrick(int x, int y) : posX(x), posY(y) {
    StoBriPixmap.load(":/new/prefix1/image/brick/stone brick.png");
    StoBriPixmap.scaled(50,50);
}

void StoneBrick::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(posX, posY, StoBriPixmap);
}

QRectF StoneBrick::boundingRect() const {
    return QRectF(posX, posY, StoBriPixmap.width(), StoBriPixmap.height());
}

void StoneBrick::setPosition(qreal x, qreal y) {
    posX = x;
    posY = y;
    setPos(posX, posY);
}

qreal StoneBrick::getY() const {
    return posY;
}

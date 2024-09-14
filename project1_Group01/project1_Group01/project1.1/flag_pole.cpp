#include "flag_pole.h"

Flag_pole::Flag_pole(int x, int y) : posX(x), posY(y)
{
    flagpolePixmap.load(":/new/prefix1/image/item/flag-pole.png");
    flagpolePixmap=flagpolePixmap.scaled(15,500);
}

void Flag_pole::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(posX, posY, flagpolePixmap);
}

QRectF Flag_pole::boundingRect() const {
    return QRectF(posX, posY, flagpolePixmap.width(), flagpolePixmap.height());
}

void Flag_pole::setPosition(qreal x, qreal y) {
    posX = x;
    posY = y;
    setPos(posX, posY);
}

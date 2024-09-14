#include "waterpipe.h"

WaterPipe::WaterPipe(int x, int y) : posX(x), posY(y) {
    pipePixmap.load(":/new/prefix1/image/brick/water pipe.png");
    candown=false;
}

void WaterPipe::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(posX, posY, pipePixmap);
}

QRectF WaterPipe::boundingRect() const {
    return QRectF(posX, posY, pipePixmap.width(), pipePixmap.height());
}

void WaterPipe::setPosition(qreal x, qreal y) {
    posX = x;
    posY = y;
    setPos(posX, posY);
}

qreal WaterPipe::getY() const {
    return posY;
}

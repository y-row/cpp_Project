#include "superstar.h"

SuperStar::SuperStar(int x, int y) : posX(x), posY(y)
{
    superstarPixmap.load(":/new/prefix1/image/super star.png");
}

void SuperStar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(posX, posY, superstarPixmap);
}

QRectF SuperStar::boundingRect() const {
    return QRectF(posX, posY, superstarPixmap.width(), superstarPixmap.height());
}

void SuperStar::setPosition(qreal x, qreal y) {
    posX = x;
    posY = y;
    setPos(posX, posY);
}

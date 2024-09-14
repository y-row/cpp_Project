#include "flag.h"

Flag::Flag(int x, int y) : posX(x), posY(y)
{
    flagPixmap.load(":/new/prefix1/image/item/flag.png");
    flagPixmap=flagPixmap.scaled(60,60);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Flag::fall);
    qDebug() << "the x-axis value of flag:"<< x;
}

void Flag::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(posX, posY, flagPixmap);
}

QRectF Flag::boundingRect() const {
    return QRectF(posX, posY, flagPixmap.width(), flagPixmap.height());
}

void Flag::setPosition(qreal x, qreal y) {
    posX = x;
    posY = y;
    setPos(posX, posY);
}

//flag穩定下降
void Flag::fall() {
    timer->start(20);
    posY += 3;  // 每次下降 3 像素
    update();  // 更新旗幟的位置
    if (posY > 460) {
        timer->stop();  // 停止計時器
    }
}

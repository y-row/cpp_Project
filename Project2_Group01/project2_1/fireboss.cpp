#include "fireboss.h"
#include <QDebug>
FireBoss::FireBoss(qreal x, qreal y)
{
    this->setPos(x,y);
    this->setAttr(fire);
    pixmap = pixmap.scaled(128, 128);
    this->attack = 400;
    this->cd = 5;
    this->originalCD=5;
    this->hp = 700;
    this->specialMechanism = burning;
    pixmap.load(":/new/prefix1/dataset/enemy/180n.png");
    pixmap = pixmap.scaled(256, 256); // 調整圖片大小
}

QRectF FireBoss::boundingRect() const {
    return QRectF(posX, posY, pixmap.width(), pixmap.height());
}

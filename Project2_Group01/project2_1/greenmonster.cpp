#include "greenmonster.h"

GreenMonster::GreenMonster(qreal x, qreal y) { // 初始化攻擊力、生命值和冷卻時間
    this->attack = 200;
    this->cd = 3;
    this->hp = 300;
    this->setPos(x,y);
    this->setAttr(earth);
    this->originalCD=3;
    pixmap = pixmap.scaled(128, 128);
    pixmap.load(":/new/prefix1/dataset/enemy/267n.png"); // 替換成你的綠色怪物圖片路徑
    pixmap = pixmap.scaled(128, 128);
    this->specialMechanism=weathering;
}

QRectF GreenMonster::boundingRect() const {
    return QRectF(posX, posY, pixmap.width(), pixmap.height());
}

#include "slime.h"

Slime::Slime(int x, int y, int attribute)
{
    this->setPos(x,y);
    this->setAttr(attribute);
    this->originalCD=3;
    initializeAttributes();
    pixmap = pixmap.scaled(128, 128);
    this->attack = 200;
    this->cd = 3;
    this->hp = 100;
    this->specialMechanism = none;
}

void Slime::initializeAttributes() {
    switch (attribute) {
    case water:
        this->pixmap.load(":/new/prefix1/dataset/enemy/96n.png");
        break;
    case fire:
        this->pixmap.load(":/new/prefix1/dataset/enemy/98n.png");
        break;
    case earth:    
        this->pixmap.load(":/new/prefix1/dataset/enemy/100n.png");
        break;
    case light:
        this->pixmap.load(":/new/prefix1/dataset/enemy/102n.png");
        break;
    case dark:
        this->pixmap.load(":/new/prefix1/dataset/enemy/104n.png");
        break;
    }
}
QString Slime::getImagePath() const {
    return "";
}

QRectF Slime::boundingRect() const {
    return QRectF(posX, posY, pixmap.width(), pixmap.height());
}

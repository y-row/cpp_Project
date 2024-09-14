#include "monster.h"

Monster::Monster(){
}
void Monster::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(posX, posY, pixmap);
}
int Monster::getAttack() const {
    return attack;
}

int Monster::getHP() const {
    return hp;
}

int Monster::getCD() const {
    return cd;
}

int Monster::getAttribute() const {
    return this->attribute;
}

int Monster::getAttackPower() const {
    return this->attack;
}

void Monster::setHP(int a) {
    this->hp = a;
    hpbar->setValue(hp);
}

void Monster::setCD(int a) {
    this->cd = a;
    originalCD = a;
}

void Monster::CDminusOne() {
    if (cd > 0) {
        this->cd--;
    }
}

qreal Monster::getX() const {
    return posX;
}

qreal Monster::getY() const {
    return posY;
}

bool Monster::Damaged(int value){
    this->hp-=value;
    if(this->hp<=0){
        return true;
    }
    return false;

}
void Monster::setPos(int x, int y){
    this->posX=x;
    this->posY=y;
}
void Monster::setAttr(int attr){
    this->attribute=attr;
}
void Monster::resetCD(){
    this->cd=originalCD;
}

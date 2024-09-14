#include "characters.h"
#include "gamebase.h"

Characters::Characters(int x, int y, int id)
{
    posX = x;
    posY = y;
    attributeType = id;
    switch (attributeType) {
    case water:
        charactersPixmap.load(":/new/prefix1/dataset/character/ID1.png");
        cd = 3;
        originalCD = cd;
        mySkill = changeAttribute;
        break;
    case fire:
        charactersPixmap.load(":/new/prefix1/dataset/character/ID2.png");
        cd = 5;
        originalCD = cd;
        mySkill = fireFall;
        break;
    case earth:
        charactersPixmap.load(":/new/prefix1/dataset/character/ID3.png");
        cd = 4;
        originalCD = cd;
        mySkill = resistant;
        break;
    case light:
        charactersPixmap.load(":/new/prefix1/dataset/character/ID4.png");
        cd = 6;
        originalCD = cd;
        mySkill = aligntime15;
        break;
    case dark:
        charactersPixmap.load(":/new/prefix1/dataset/character/ID5.png");
        cd = 7;
        originalCD = cd;
        mySkill = changetonormalstone;
        break;
    }

}

void Characters::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(posX, posY, charactersPixmap);
}

QRectF Characters::boundingRect() const {
    return QRectF(posX, posY, charactersPixmap.width(), charactersPixmap.height());
}

void Characters::setPosition(qreal x, qreal y) {
    posX = x;
    posY = y;
    setPos(posX, posY);
}

/*bool Characters::useSkill(int *damage, int *NCAR, int a, int b){ //可不可以點擊在外面判斷 bool:combo類判斷
 * *damage:直傷類
 * *NCAR: 依照浮石數量增加傷害類
 * a: 目標顏色
 * b: 選定的顏色(或隨機)
 * health: 直接回復500
 *

    this->cd=originalCD;
    switch(this->mySkill){
        case changeAttribute:
            for(int i=0;i<6;i++){
                for(int j=0;j<5;j++){
                    if(Runestone::rune[i][j]->getType()==b){
                        Runestone::rune[i][j]->changeType(a);
                        Runestone::attributemap[i][j]=a;
                    }
                }
            }
        break;
        case health:
            GameBase::staticplusHP(500);//a為加多少，damage為要傳入plusPlayerHP的數

        break;
        default:
            *damage+=20;
    }

    return false;
}*/

void Characters::minusOneCD(){
    --cd;
    if (cd <= 0)
        cd = 0;
}

int Characters::getskill(){
    return mySkill;
}

#ifndef MONSTER_H
#define MONSTER_H

#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QPixmap>
#include <QPainter>
#include <QProgressBar>
#include "runestone.h"

enum skill{none,weathering,burning}; //風化 or 燃燒
class Monster :public QGraphicsObject
{
public:
    Monster();
    int getAttack() const;
    int getHP() const;
    int getCD() const;
    int getAttribute() const;
    int getAttackPower() const;

    void setHP(int a);
    void setCD(int a);
    void CDminusOne();
    bool Damaged(int value); //判斷受傷的函數
    qreal getX() const;
    qreal getY() const;
    void setPos(int x, int y);
    void setAttr(int attr);
    void resetCD();
    //void initMonster(int x, int y, int attr, int hp, int cd, int attack);
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    qreal posX;
    qreal posY;
    QProgressBar *hpbar;    //血條
    int attack;
    int hp;
    int cd;
    int specialMechanism;
    int originalCD; // 存原本的CD值
    int attribute;

    QPixmap pixmap;

};

#endif // MONSTER_H

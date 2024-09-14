#include "bullet.h"
#include "toxic_mushroom.h"
#include <cmath>
#include "flower.h"
#include "coin.h"
Bullet::Bullet(qreal x, qreal y, qreal mouseX, qreal mouseY) : posX(x), posY(y)
{
    double a = (mouseX - x) * (mouseX - x);
    double b = (mouseY - y) * (mouseY - y);
    double c = pow(a+b,0.5);

    vx = 20*(mouseX - x)/c;
    vy = 20*(mouseY - y)/c;

    bulletPixmap.load(":/new/prefix1/image/bullet.png");
    bulletPixmap=bulletPixmap.scaled(20,20);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Bullet::move);  // 連接信號與槽
    timer->start(30);
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(posX, posY, bulletPixmap);
}

QRectF Bullet::boundingRect() const {
    return QRectF(posX, posY, bulletPixmap.width(), bulletPixmap.height());
}

void Bullet::setPosition(qreal x, qreal y) {
    posX = x;
    posY = y;
    setPos(posX, posY);
}

void Bullet::move(){
    posX += vx;
    posY += vy;
    moveBy(vx,vy);
    //update();
    QList<QGraphicsItem*> collidingList = collidingItems(Qt::IntersectsItemBoundingRect);
    for (QGraphicsItem* item : collidingList) {
        Toxic_mushroom *toxicmushroom = dynamic_cast<Toxic_mushroom*>(item);
        Turtle *turtle = dynamic_cast<Turtle*>(item);
        Mario *mario =dynamic_cast<Mario*>(item);
        Flower *flower = dynamic_cast<Flower*>(item);
        Coin *currentcoin =dynamic_cast<Coin*>(item);
        //碰到東西都移除子彈
        if(turtle){
            delete turtle;
            delete this;
        }
        else if(flower){
            delete flower;
        }
        else if (toxicmushroom){
            delete  toxicmushroom;
            delete this;
        }
        if(mario){
            continue;
        }
        if(currentcoin){
            continue;
        }
        delete this;
    }
}

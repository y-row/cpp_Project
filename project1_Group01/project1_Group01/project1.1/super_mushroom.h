#ifndef SUPER_MUSHROOM_H
#define SUPER_MUSHROOM_H

#include <QGraphicsObject>
#include <QPainter>
#include <QTimer>
#include "bullet.h"
#include "floor.h"
#include "waterpipe.h"
#include "normalbrick.h"
#include "stonebrick.h"
#include "boxbrick.h"
#include "brokenbrick.h"
#include "toxic_mushroom.h"
#include "mario.h"

class Super_mushroom : public QGraphicsObject
{
    Q_OBJECT
public:
    Super_mushroom(int x, int y);
    QRectF boundingRect() const override; // 返回繪製區域
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override; // 繪製函式
    void setPosition(qreal x, qreal y); // 設置位置函式
    void move();

private:
    QPixmap mushroomPixmap; // 圖片
    qreal posX; // x座標
    qreal posY; // y座標
    int vx;  //水平移動速度
    int vy; //垂直移動速度
    int g;  //重力加速度
    QTimer *timer;
};

#endif // SUPER_MUSHROOM_H

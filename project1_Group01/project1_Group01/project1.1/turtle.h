#ifndef TURTLE_H
#define TURTLE_H

#include <QGraphicsObject>
#include <QPainter>
#include <QTimer>
#include <QTimerEvent>
#include "floor.h"
#include "waterpipe.h"
#include "normalbrick.h"
#include "stonebrick.h"
#include "boxbrick.h"
#include "brokenbrick.h"
#include "mario.h"
#include "toxic_mushroom.h"
#include "bullet.h"

class Turtle : public QGraphicsObject {
    Q_OBJECT
public:
    Turtle(int x, int y); // 建構函式
    QRectF boundingRect() const override; // 返回繪製區域
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override; // 繪製函式
    void setPosition(qreal x, qreal y); // 設置位置函式
    QRectF collisionRect() const; // 新增碰撞矩形函式
    qreal getY() const;
    qreal getX() const;
    void move();
    bool shell; //龜殼狀態

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    QPixmap TurtlePixmap; // 圖片
    qreal posX; // x座標
    qreal posY; // y座標
    QTimer *timer;
    int vx;  //水平移動速度
    int vy; //垂直移動速度
    int g;  //重力加速度
    int timerID;
    int time1;  //動畫的計時器
    int time2;  //第1次踩到第2次踩的最大間隔時間
    bool spin;  //是否踩到第2次

};


#endif // TURTLE_H
